/**
* @file mainwindow.cpp
* Contains function definitions for features within the mainwindow
*
*/



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

// cpp headers
#include <new>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "model.h"

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

 

    //create a light 
  

    mapper = vtkSmartPointer<vtkDataSetMapper>::New();

    // initialisation for features
    light = vtkSmartPointer<vtkLight>::New();


    boxWidget = vtkSmartPointer<vtkBoxWidget>::New();

    // Define icon Files
    // file is determined by where you run the exe from
    // if you run withing debug then ../.. if in build then ../
    ui->actionOpen->setIcon(QIcon("../Icons/fileopen.png"));

    //configuration for all QT interactions
    // Push buttons
    connect(ui->cameraReset, &QPushButton::released, this, &MainWindow::handleResetView);
    connect(ui->ObjectColor, &QPushButton::released, this, &MainWindow::handleObjectColor);
    connect(ui->BackgroundColor, &QPushButton::released, this, &MainWindow::handleBackgroundColor);

    // --------- Filters--------------
    connect(ui->clipFilter, &QCheckBox::released, this, &MainWindow::handleClip);
    connect(ui->shrinkFilter, &QCheckBox::released, this, &MainWindow::handleShrink);

    // Tool bar actions/button
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::actionOpen);
    connect(ui->widgetBox, &QAction::toggled, this, &MainWindow::widgetBox);

    //Distance widget
    connect(ui->distWid, &QCheckBox::released, this, &MainWindow::handledistWid);

    //Axis widget
    connect(ui->axisLabel, &QAction::toggled, this, &MainWindow::AxisLabel);

 


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


    
    // Add the actor to the scene
    renderer->AddLight(light);


}

/**
*  Delets the ui
**/
MainWindow::~MainWindow()
{
    delete ui;
}
/**
*
*/
void MainWindow::on_editFilters_clicked()
{
  opFilterDialog->show();
}

void MainWindow::updateClipOriginX(int value)
{
  double newValue = value/10;
  clipOriginX = newValue;
  if(ui->clipFilter->isChecked()==true)
      handleClip();
}

void MainWindow::updateClipOriginY(int value)
{
  double newValue = value/10;
  clipOriginY = newValue;
  if(ui->clipFilter->isChecked()==true)
      handleClip();
}

void MainWindow::updateClipOriginZ(int value)
{
  double newValue = value/10;
  clipOriginZ = newValue;
  if(ui->clipFilter->isChecked()==true)
      handleClip();

}

void MainWindow::updateClipNormalX(int value)
{
  clipNormalX = value;
  if(ui->clipFilter->isChecked()==true)
      handleClip();
}

void MainWindow::updateClipNormalY(int value)
{
  clipNormalY = value;
  if(ui->clipFilter->isChecked()==true)
      handleClip();
}
void MainWindow::updateClipNormalZ(int value)
{
  clipNormalZ = value;
  if(ui->clipFilter->isChecked()==true)
      handleClip();
}

void MainWindow::updateShrinkFactor(int value)
{
//  std::cout<<"in update"<<endl;
  shrinkFactor = double(value);
  shrinkFactor = shrinkFactor/100;
  if(ui->shrinkFilter->isChecked()==true)
      handleShrink ();

}

void MainWindow::handleClip()
{


  if(ui->clipFilter->isChecked()==true)
  {

    // uncheck all other Filters
    ui->shrinkFilter->setChecked(false);

    // this will apply a clipping plane whose normal is the x-axis that crosses the x-axis at x=0
    vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
    planeLeft->SetOrigin(clipOriginX, clipOriginY, clipOriginZ);
    planeLeft->SetNormal(clipNormalX, clipNormalY, clipNormalZ);

    vtkSmartPointer<vtkClipDataSet> vtkClipFilter
                        = vtkSmartPointer<vtkClipDataSet>::New();
    // gets the output of the current using the vtkalgorithm created
    // in each model viewer function
    vtkClipFilter->SetInputConnection(source->GetOutputPort() );
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


  if(ui->shrinkFilter->isChecked()==true)
  {
    // uncheck all other Filters
    ui->clipFilter->setChecked(false);

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



void MainWindow::actionOpen()
{
  // open file explorer

  QString fileName = QFileDialog::getOpenFileName(this, tr("Open Model File"),
    "C:/",
  tr("Model Files (*.stl *.mod)"));
  // check if stl or if mod
  if(fileName.endsWith(".stl", Qt::CaseSensitive) )
  {
    // convert to cpp string
    std::string inputFilename = fileName.toLocal8Bit().constData();

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
    actor->SetMapper(mapper);

    renderer->AddActor(actor);



    // create a copy of the current source to be used with filters if necessary
    source = actor->GetMapper()->GetInputConnection(0, 0)->GetProducer();
    // Setup the renderers's camera
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();


    resetFilter();
  }

  if(fileName.endsWith(".mod", Qt::CaseSensitive) )
  {
  //  std::cout<<"yeet1";
    // convert to cpp string
    std::string inputFilename = fileName.toLocal8Bit().constData();

    if(ui->widgetBox->isChecked() )
    {
      ui->widgetBox->toggle();
      boxWidget->Off();
      interactor->TerminateApp();
    }

    // create a model file for reading
    model readModFile;
    // input file name to model
    readModFile.readFile(inputFilename.c_str());

    vtkSmartPointer<vtkPoints> vertices =
            vtkSmartPointer<vtkPoints>::New();
    // inserting every vector in model to vtkpoints
    for(int i = 0; i<readModFile.getVectorList().size(); i++) // get vectorlist.size works
    {
              //std::cout<<"hello";
      //new double x[] = readModFile.getVectorList();
      // readModFile.getVectorList.getxyz() works
            //  std::cout<<readModFile.getVectorList()[i].getX();
      vertices->InsertPoint(i, readModFile.getVectorList()[i].getX(),
                               readModFile.getVectorList()[i].getY(),
                               readModFile.getVectorList()[i].getZ() );
    }

    vtkSmartPointer<vtkUnstructuredGrid> ugrid =
            vtkSmartPointer<vtkUnstructuredGrid>::New();
    ugrid->Allocate(500);
    // loop for every cell
      // depending on cell type eg pyramid hex, tetra cube
    for(int n = 0; n<readModFile.getCells().size(); n++)
    {
      // HEX
      if(readModFile.getCells()[n].getType()=='h')
      {
        //int *vectorIds;
        //vectorIds = new int[8];
        static vtkIdType vectorIds[8];
        // hexahedron has 8 points/vertices
        // populate array with vector ids of the current cell
        for(int j = 0; j<8; j++)
        {
          //float test = readModFile.getCells()[n].getThisCellVectorIdList()[j];
          //std::cout<test;

          vectorIds[j] = readModFile.getCells()[n].getThisCellVectorIdList()[j]; // success gets ids
      //    std::cout<<vectorIds[j]<<"\n";
        }
        // inserts hex cells
        ugrid->InsertNextCell(VTK_HEXAHEDRON, 8, vectorIds);

      }
      // TETRA
      if(readModFile.getCells()[n].getType()=='t')
      {
        static vtkIdType vectorIds[4];
        for(int j = 0; j<4; j++)
        {
          vectorIds[j] = readModFile.getCells()[n].getThisCellVectorIdList()[j];
        }
        ugrid->InsertNextCell(VTK_TETRA, 8, vectorIds);

      }

      // PYRAMID
      if(readModFile.getCells()[n].getType()=='p')
      {
        static vtkIdType vectorIds[5];
        for(int j = 0; j<5; j++)
        {
          vectorIds[j] = readModFile.getCells()[n].getThisCellVectorIdList()[j];
        }
        ugrid->InsertNextCell(VTK_PYRAMID, 5, vectorIds);

      }

    }

    // map the model
    ugrid->SetPoints(vertices);

    mapper->SetInputData(ugrid);
    actor->SetMapper(mapper);
    renderer->AddActor(actor);

    source = actor->GetMapper()->GetInputConnection(0, 0)->GetProducer();

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

    resetFilter();

  }


}

//Change object color
void MainWindow::handleObjectColor()
{
    QColor QTcolor = QColorDialog::getColor(Qt::white, this);
    if (QTcolor.isValid())
    {
        actor->GetProperty()->SetColor(QTcolor.redF(), QTcolor.greenF(), QTcolor.blueF());
        //ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );
        //ui->qvtkWidget->GetRenderWindow()->Render();
        renderWindow->Render();
    }
}

//Change background color
void MainWindow::handleBackgroundColor()
{
    QColor QTcolor = QColorDialog::getColor(Qt::white, this);
    if (QTcolor.isValid())
    {
        renderer->SetBackground(QTcolor.redF(), QTcolor.greenF(), QTcolor.blueF());
      //  ui->qvtkWidget->GetRenderWindow()->Render();
      renderWindow->Render();

    }
}


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

    
    ui->qvtkWidget->GetRenderWindow()->Render();
}

//function to see the Edge of the object
void MainWindow::on_Edge_toggled(bool checked)
{

    if (checked)
    {
        actor->GetProperty()->SetRepresentationToWireframe();
        
    }
    else 
    {
        actor->GetProperty()->SetRepresentationToSurface();
        
    }
    ui->qvtkWidget->GetRenderWindow()->Render();
}

//Distance widget
void MainWindow::handledistWid()
{
    //if the checkbox is checked
    if (ui->distWid->isChecked() == true)
    {
        //Turn on the distance widget
        distanceWidget = vtkSmartPointer<vtkDistanceWidget>::New();
        distanceWidget->SetInteractor(ui->qvtkWidget->GetRenderWindow()->GetInteractor());
        distanceWidget->CreateDefaultRepresentation();
        distanceWidget->On();
        renderWindow->Render();
    }
    //if the checkbox is not check
    else if (ui->distWid->isChecked() == false)
    {
        //Turn off the distance widget   
        mapper->SetInputConnection(source->GetOutputPort());

        actor->SetMapper(mapper);

        renderer->RemoveAllViewProps();
        renderer->AddActor(actor);
        distanceWidget->Off();
        renderWindow->Render();
    }
}

// opacity ///

void MainWindow::on_OpacitySlider_valueChanged(int value)
{
    if (ui->OpacitySlider->value() <= 1) actor->GetProperty()->SetOpacity(1.0);
    else  actor->GetProperty()->SetOpacity(1 - (double)ui->OpacitySlider->value() / 100);
    ui->qvtkWidget->GetRenderWindow()->Render();
}

//Axis label
void MainWindow::AxisLabel()
{
    //if the checkbox is checked
    if (ui->axisLabel->isChecked() == true)
    {
        //Turn on the axis widget
        orientationWidget->SetOrientationMarker(axes);
        orientationWidget->SetInteractor(ui->qvtkWidget->GetRenderWindow()->GetInteractor());
        orientationWidget->SetEnabled(1);
        orientationWidget->InteractiveOff();
        renderWindow->Render(); 
    }
    //if the checkbox is not check
    else if (ui->axisLabel->isChecked() == false)
    {
        //Turn off the axis widget
        orientationWidget->Off();
        renderWindow->Render();
    }
    }
    

