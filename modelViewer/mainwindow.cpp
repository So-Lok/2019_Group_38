/********************************************************************************
* @file mainwwindow.cpp
* @brief Contains function definitions for features within the mainwindow
*
* Type of features
* - Filters
*
**********************************************************************************/



// vtk headers

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkGenericOpenGLRenderWindow.h>

// sources
#include <vtkCubeSource.h>

// reading
#include <vtkSTLReader.h>
#include <vtkPolyDataMapper.h>

// used in pyramid
#include <vtkPoints.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPyramid.h>
#include <vtkCellArray.h>

// filters
#include <vtkPlane.h>
#include <vtkClipDataSet.h>
#include <vtkShrinkFilter.h>

// color
#include <vtkNamedColors.h>

//light
#include <vtkLight.h>

// Box widget
#include <vtkInteractorStyleTrackballCamera.h>


// QT headers for opening a file

//#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"


/**
 *
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Initialise additional windows
    opFilterDialog = new optionsFilter(this);

    // note that qvtkWidget is the object name of the QtVTKOpenGLWidget
    ui->qvtkWidget->SetRenderWindow( renderWindow );
    renderer = vtkSmartPointer<vtkRenderer>::New();
    // render window made in qt and therefore assign the renderer to the qt window
    ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
    actor = vtkSmartPointer<vtkActor>::New();
    mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    //source = actor->GetMapper()->GetInputConnection(0, 0)->GetProducer();

    // initialisation for features
    light = vtkSmartPointer<vtkLight>::New();

    boxWidget = vtkSmartPointer<vtkBoxWidget>::New();

    // Define icon Files
    // file is determined by where you run the exe from
    // if you run withing debug then ../.. if in build then ../
    ui->actionOpen->setIcon(QIcon("../Icons/fileopen.png"));

    //configuration for all QT interactions
    // Push buttons
    connect(ui->cubeButton, &QPushButton::released, this, &MainWindow::handleCube);
    connect(ui->pyramidButton, &QPushButton::released, this, &MainWindow::handlePyrmaid);
    connect(ui->cameraReset, &QPushButton::released, this, &MainWindow::handleResetView);
    connect(ui->ObjectColor, &QPushButton::released, this, &MainWindow::handleObjectColor);
    connect(ui->BackgroundColor, &QPushButton::released, this, &MainWindow::handleBackgroundColor);

    // --------- Filters--------------
    connect(ui->clipFilter, &QCheckBox::released, this, &MainWindow::handleClip);
    connect(ui->shrinkFilter, &QCheckBox::released, this, &MainWindow::handleShrink);

    // Tool bar actions/button
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::actionOpen);
    connect(ui->widgetBox, &QAction::toggled, this, &MainWindow::widgetBox);


    // SIGNAL(External window) connection to SLOTs(MainWindow)

    // --------------------Clip Filter--------------------
    connect(opFilterDialog, SIGNAL(sendClipOriginX(int)), this, SLOT(updateClipOriginX(int) ) );
    connect(opFilterDialog, SIGNAL(sendClipOriginY(int)), this, SLOT(updateClipOriginY(int) ) );
    connect(opFilterDialog, SIGNAL(sendClipOriginZ(int)), this, SLOT(updateClipOriginZ(int) ) );

    connect(opFilterDialog, SIGNAL(sendClipNormalX(int)), this, SLOT(updateClipNormalX(int) ) );
    connect(opFilterDialog, SIGNAL(sendClipNormalY(int)), this, SLOT(updateClipNormalY(int) ) );
    connect(opFilterDialog, SIGNAL(sendClipNormalZ(int)), this, SLOT(updateClipNormalZ(int) ) );
    //--------------------Clip Filter---------------------------------
    // shrink filter
    connect(opFilterDialog, SIGNAL(sendShrinkFactor(int)), this, SLOT(updateShrinkFactor(int) ) );



    // start up
    renderer->RemoveAllViewProps();

    /////light intensity/////

    light = vtkSmartPointer<vtkLight>::New();
    light->SetLightTypeToSceneLight();
    light->SetPosition(5, 5, 15);
    light->SetPositional(true);
    light->SetConeAngle(10);
    light->SetFocalPoint(0, 0, 0);
    light->SetDiffuseColor(1, 1, 1);
    light->SetAmbientColor(1, 1, 1);
    light->SetSpecularColor(1, 1, 1);
    light->SetIntensity(0.5);
}

/**
* @function mainwindow destructor
**/
MainWindow::~MainWindow()
{
    delete ui;
}
/**
* @function
*/
void MainWindow::on_editFilters_clicked()
{
  opFilterDialog->show();
}

void MainWindow::updateClipOriginX(int value)
{
  double newValue = value/10;
  clipOriginX = newValue;
  handleClip();
}

void MainWindow::updateClipOriginY(int value)
{
  double newValue = value/10;
  clipOriginY = newValue;
  handleClip();
}

void MainWindow::updateClipOriginZ(int value)
{
  double newValue = value/10;
  clipOriginZ = newValue;
  handleClip();

}

void MainWindow::updateClipNormalX(int value)
{
  clipNormalX = value;
  handleClip();
}

void MainWindow::updateClipNormalY(int value)
{
  clipNormalY = value;
  handleClip();
}
void MainWindow::updateClipNormalZ(int value)
{
  clipNormalZ = value;
  handleClip();
}

void MainWindow::updateShrinkFactor(int value)
{
//  std::cout<<"in update"<<endl;
  shrinkFactor = double(value);
  shrinkFactor = shrinkFactor/100;
  handleShrink();

}

void MainWindow::handleClip()
{
  // uncheck all other Filters
  ui->shrinkFilter->setChecked(false);

  if(ui->clipFilter->isChecked()==true)
  {
    // this will apply a clipping plane whose normal is the x-axis that crosses the x-axis at x=0
    vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
    planeLeft->SetOrigin(clipOriginX, clipOriginY, clipOriginZ);
    planeLeft->SetNormal(clipNormalX, clipNormalY, clipNormalZ);

    vtkSmartPointer<vtkClipDataSet> vtkClipFilter
                        = vtkSmartPointer<vtkClipDataSet>::New();
    // gets the output of the current using the vtkalgorithm created
    // in each model viewer function
  //  vtkClipFilter->SetInputConnection(actor->GetMapper()->GetInputConnection(0, 0)->GetProducer()->GetOutputPort() );
    vtkClipFilter->SetInputConnection(source->GetOutputPort() );
    // could change source to actor->GetMapper()->GetInputConnection(0, 0)->GetProducer()
    // however becuase it is the inital filter it isn't exactly necessary

    vtkClipFilter->SetClipFunction( planeLeft.Get() );

    mapper->SetInputConnection(vtkClipFilter->GetOutputPort() );
    actor->SetMapper(mapper);

    renderer->RemoveAllViewProps();
    renderer->AddActor(actor);
    renderWindow->Render();
  }
  else if(ui->clipFilter->isChecked()==false)
  {
    mapper->SetInputConnection(source->GetOutputPort() );
    actor->SetMapper(mapper);

    renderer->RemoveAllViewProps();
    renderer->AddActor(actor);
    renderWindow->Render();

  }



}

void MainWindow::handleShrink()
{
  // uncheck all other Filters
  ui->clipFilter->setChecked(false);

  if(ui->shrinkFilter->isChecked()==true)
  {
    vtkSmartPointer<vtkShrinkFilter> shrinkFilter
                    = vtkSmartPointer<vtkShrinkFilter>::New();
    shrinkFilter->SetInputConnection(source->GetOutputPort() );
    shrinkFilter->SetShrinkFactor(shrinkFactor);
    shrinkFilter->Update();

    mapper->SetInputConnection(shrinkFilter->GetOutputPort() );
    actor->SetMapper(mapper);

    renderer->RemoveAllViewProps();
    renderer->AddActor(actor);
    renderWindow->Render();
  }
  else if(ui->shrinkFilter->isChecked()==false)
  {
    mapper->SetInputConnection(source->GetOutputPort() );
    actor->SetMapper(mapper);

    renderer->RemoveAllViewProps();
    renderer->AddActor(actor);
    renderWindow->Render();

  }
}

void MainWindow::resetFilter()
{
  // uncheck all filters
  ui->clipFilter->setChecked(false);
  ui->shrinkFilter->setChecked(false);

  mapper->SetInputConnection(source->GetOutputPort() );
  actor->SetMapper(mapper);

  renderer->RemoveAllViewProps();
  renderer->AddActor(actor);
  renderWindow->Render();
}



// Resets the of the model, both zoom and rotation of the model
// to  a default which can be set

void MainWindow::handleResetView()

{
  // New camera pointer is created
  camera = vtkSmartPointer<vtkCamera>::New();

  // 0,0,0 focal point is default when making new camera
  //  camera->SetFocalPoint(5,5,5);

  // set the current camera of the renderer to the newly created camera
  renderer->SetActiveCamera(camera);
  // resets the cameras zoom settings
  renderer->ResetCamera();
  // makes it so that the model will not clip outside of the rendering window
  renderer->ResetCameraClippingRange();
  // updates the render window
  renderWindow->Render();
}


// for mod get rid of pyramid and cube buttons so that they are used by inserting points

/**
* @function generates a pyramid
*/
void MainWindow::handlePyrmaid()
{
  // create a array of points
  vtkSmartPointer<vtkPoints> points =
                  vtkSmartPointer<vtkPoints>::New();

  // preset some coords
  float p0[3] = {1.0, 1.0, 1.0};
  float p1[3] = {-1.0, 1.0, 1.0};
  float p2[3] = {-1.0, -1.0, 1.0};
  float p3[3] = {1.0, -1.0, 1.0};
  float p4[3] = {0.0, 0.0, 0.0};
  // adds points to the smart pointer "points"
  points->InsertNextPoint(p0);
  points->InsertNextPoint(p1);
  points->InsertNextPoint(p2);
  points->InsertNextPoint(p3);
  points->InsertNextPoint(p4);


  vtkSmartPointer<vtkPyramid> pyramid =
                  vtkSmartPointer<vtkPyramid>::New();
  // get set pyramid point ids
  pyramid->GetPointIds()->SetId(0,0);
  pyramid->GetPointIds()->SetId(1,1);
  pyramid->GetPointIds()->SetId(2,2);
  pyramid->GetPointIds()->SetId(3,3);
  pyramid->GetPointIds()->SetId(4,4);

  vtkSmartPointer<vtkCellArray> cells =
                  vtkSmartPointer<vtkCellArray>::New();
  // 1 pyrmaid cell, group work should have multiple that are combined
  cells->InsertNextCell (pyramid);

  vtkSmartPointer<vtkUnstructuredGrid> ug =
                  vtkSmartPointer<vtkUnstructuredGrid>::New();
  // setup grid using points
  ug->SetPoints(points);
  // insert cell, pyramid
  ug->InsertNextCell(pyramid->GetCellType(),pyramid->GetPointIds());

  //Create an actor and mapper
  colors = vtkSmartPointer<vtkNamedColors>::New();

  //light intensity
  vtkSmartPointer<vtkLight> light =
      vtkSmartPointer<vtkLight>::New();

  //vtkSmartPointer<vtkDataSetMapper>
  mapper = vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputData(ug);

//  vtkSmartPointer<vtkActor> actor =
  //    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->EdgeVisibilityOff();

  // clear old render and add new one
  renderer->RemoveAllViewProps();
  renderer->AddActor(actor);

  // create a copy of the current source to be used with filters if necessary
  source = actor->GetMapper()->GetInputConnection(0, 0)->GetProducer();

  //---- reset the camera angle------
  camera = vtkSmartPointer<vtkCamera>::New();
  // 0,0,0 focal point is default when making new camera
  //camera->SetFocalPoint(0,0,0);
//  camera->SetFocalPoint(0,-10,0);
//  renderer->SetActiveCamera(camera);
  renderer->ResetCamera(); // resets the zoom
  renderer->ResetCameraClippingRange(); // if the model is zoomed offscreen
  // /reset camera angle----------------

  // render the pyramid as soon as button is pushed
  renderWindow->Render();

  //updateFilters();
}

void MainWindow::handleCube()
{
  // Create a cube using a vtkCubeSource
  vtkSmartPointer<vtkCubeSource> cubeSource =
                  vtkSmartPointer<vtkCubeSource>::New();

  renderer->RemoveAllViewProps();

  // Create a mapper that will hold the cube's geometry in a format suitable for
  // rendering
  mapper = vtkSmartPointer<vtkDataSetMapper>::New();

  mapper->SetInputConnection(cubeSource->GetOutputPort());
  actor->SetMapper(mapper);

  actor->GetProperty()->EdgeVisibilityOff();

  //light intensity
  vtkSmartPointer<vtkLight> light =
      vtkSmartPointer<vtkLight>::New();

  // Add the actor to the scene
  renderer->AddActor(actor);

  // create a copy of the current source to be used with filters if necessary
  source = actor->GetMapper()->GetInputConnection(0, 0)->GetProducer();

  // changes the zoom of the camera so that the model fits onto the screen
  renderer->ResetCamera(); // resets the zoom and location of camera
  renderer->ResetCameraClippingRange(); // if the model is zoomed offscreen
  //  renderer->GetActiveCamera()->Azimuth(30);
  //  renderer->GetActiveCamera()->Elevation(30);

  renderWindow->Render();

  //updateFilters();

}

/**
*  @function
*
**/
void MainWindow::widgetBox()
{
  if(ui->widgetBox->isChecked() )
  {
    interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow( renderWindow );

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
                      vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    // qvtk is the open gl  render window
    interactor->SetInteractorStyle(style); //->GetRenderWindow() after qvtk

    boxWidget->SetInteractor(interactor );

    boxWidget->SetProp3D( actor );
    boxWidget->SetPlaceFactor( 1.25 ); // Make the box 1.25x larger than the actor
    boxWidget->PlaceWidget();

    vtkSmartPointer<vtkMyCallback> callback =
                    vtkSmartPointer<vtkMyCallback>::New();
    boxWidget->AddObserver( vtkCommand::InteractionEvent, callback );

    boxWidget->On();

    renderWindow->Render();
    interactor->Start();


  }
  else
  {
    interactor->TerminateApp();
    boxWidget->Off();
    renderWindow->Render();

  }

}


/**
* @function Allows the user to import a STL file into the renderer
*/
void MainWindow::actionOpen()
{
  // open file explorer

  QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"),
    "C:/",
  tr("STL Files (*.stl)"));

  // set file up with a reader
  std::string inputFilename = fileName.toLocal8Bit().constData();
  //std::string inputFilename = fileName;

  if(ui->widgetBox->isChecked() )
  {
    ui->widgetBox->toggle();
    boxWidget->Off();
    interactor->TerminateApp();
  }

  vtkSmartPointer<vtkSTLReader> reader =
                  vtkSmartPointer<vtkSTLReader>::New();

  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  // clear props in old renderer

  renderer->RemoveAllViewProps();

  // visualise the stl
  // private variable mapper for DataSetMappper
  vtkSmartPointer<vtkPolyDataMapper> polyMapper
                              = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

//  vtkSmartPointer<vtkActor> actor =
  //                vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  //colors = vtkSmartPointer<vtkNamedColors>::New();

  ///for light intensity//
  vtkSmartPointer<vtkLight> light =
      vtkSmartPointer<vtkLight>::New();

  renderer->AddActor(actor);

  // create a copy of the current source to be used with filters if necessary
  source = actor->GetMapper()->GetInputConnection(0, 0)->GetProducer();
  currentModel = actor->GetMapper()->GetInputConnection(0, 0)->GetProducer();

  // Setup the renderers's camera
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCameraClippingRange();

  // Render the new model straight away
  //renderWindow->Render();

  resetFilter();
}


//Change object color
void MainWindow::handleObjectColor()
{
    QColor QTcolor = QColorDialog::getColor(Qt::white, this);
    if (QTcolor.isValid())
    {
        actor->GetProperty()->SetColor(QTcolor.redF(), QTcolor.greenF(), QTcolor.blueF());
        //ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );
        ui->qvtkWidget->GetRenderWindow()->Render();
    }
}

//Change background color
void MainWindow::handleBackgroundColor()
{
    QColor QTcolor = QColorDialog::getColor(Qt::white, this);
    if (QTcolor.isValid())
    {
        renderer->SetBackground(QTcolor.redF(), QTcolor.greenF(), QTcolor.blueF());
        ui->qvtkWidget->GetRenderWindow()->Render();

    }
}

/**
* @function override of CloseEvent
*
* Used to terminate interactor if box widget is running whilst closing
*/
void MainWindow::closeEvent (QCloseEvent *event)
{
  // checckBox is for box widget
  if(ui->checkBox->isChecked())
    interactor->TerminateApp();
}




void MainWindow::on_Slider_sliderMoved(int position)
{
    if (ui->checkBox->isChecked()) {
        light->SetIntensity((float)(100 - position) / 100);
    }
    else {
        light->SetIntensity(0.5);
    }
    renderer->AddLight(light);
    ui->qvtkWidget->GetRenderWindow()->Render();


}

//checked box before adjust the light intensity
void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked) {
        light->SetIntensity((float)(100 - ui->Slider->value()) / 100);
    }
    else {
        light->SetIntensity(0.5);
    }

    renderer->AddLight(light);
    ui->qvtkWidget->GetRenderWindow()->Render();
}
