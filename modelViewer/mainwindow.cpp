// mainwindow.cpp

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

// colour
#include <vtkNamedColors.h>

// Box widget
#include <vtkBoxWidget.h>
#include <vtkCommand.h>
#include <vtkTransform.h>


// QT headers for opening a file

//#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h" 

//include to implement the x/y/z axes  
#include <vtkAxesActor.h> 
#include <vtkTransform.h>


/** @file
 * This file defines the functions used in the mainwindow
 */

/**
 *
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // standard call to setup the qt ui
    ui->setupUi(this);

    // Now need to create a VTK render window and link it to the QtVTK widget
    // Render window is created as a private variable in .h

    // note that qvtkWidget is the object name of the QtVTKOpenGLWidget
    ui->qvtkWidget->SetRenderWindow( renderWindow );
    // Create a renderer, and render window
    renderer = vtkSmartPointer<vtkRenderer>::New();
    // render window made in qt and therefore assign the renderer to the qt window
    ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
    //no need to tell widget to render and start the interaction, qt does this

    actor = vtkSmartPointer<vtkActor>::New(); 

	//smart pointer to VTKCamera 
	vtkSmartPointer<vtkCamera> camera =
		vtkSmartPointer<vtkCamera>::New();

    // Define icon Files
    // file is determined by where you run the exe from
    // if you run withing debug then ../.. if in build then ../
    ui->actionOpen->setIcon(QIcon("../Icons/fileopen.png"));

    // configure actions and pushbuttons
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::actionOpen);
    connect(ui->cubeButton, &QPushButton::released, this, &MainWindow::handleCube);
    connect(ui->pyramidButton, &QPushButton::released, this, &MainWindow::handlePyrmaid);
    connect(ui->cameraReset, &QPushButton::released, this, &MainWindow::handleResetView);
    connect(ui->clipFilter, &QCheckBox::released, this, &MainWindow::updateFilters);
    connect(ui->shrinkFilter, &QCheckBox::released, this, &MainWindow::updateFilters);
<<<<<<< HEAD
    connect(ui->ObjectColor, &QPushButton::released, this, &MainWindow::handleObjectColor);
    connect(ui->BackgroundColor, &QPushButton::released, this, &MainWindow::handleBackgroundColor);
=======
   
>>>>>>> 4b0aaa701a9c6f2cfd3914b3ffb6d2a64c278bb4

//implementation of the camera botton's change for camera change 

connect(ui->xaxisButton, &QPushButton::released, this, &MainWindow::handleViewx);
connect(ui->xaxisButton2, &QPushButton::released, this, &MainWindow::handleViewx2);

    // default model cube
    handleCube();


}

MainWindow::~MainWindow()
{
    delete ui;
}




// function for updating render with filters

void MainWindow::updateFilters()
{
  if(ui->clipFilter->isChecked()==true)
      applyClip = true;
  else if(ui->clipFilter->isChecked()==false)
      applyClip = false;

  if(ui->shrinkFilter->isChecked()==true)
      applyShrink = true;
  else if(ui->shrinkFilter->isChecked()==false)
      applyShrink = false;

  // reset everything if one of the the filters is unchecked
  if(applyClip == false || applyShrink == false)
  {
    mapper->SetInputConnection(source->GetOutputPort() );

    //actor = vtkSmartPointer<vtkActor>::New();

    actor->SetMapper(mapper);

    renderer->RemoveAllViewProps();
    renderer->AddActor(actor);
    renderWindow->Render();
  }


  // Apply all filters which have been checked
  if(applyClip == true)
  {
    // this will apply a clipping plane whose normal is the x-axis that crosses the x-axis at x=0
    vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
    planeLeft->SetOrigin(0.0, 0.0, 0.0);
    planeLeft->SetNormal(-1.0, 0.0, 0.0);

    vtkSmartPointer<vtkClipDataSet> vtkClipFilter
                        = vtkSmartPointer<vtkClipDataSet>::New();
    // gets the output of the current using the vtkalgorithm created
    // in each model viewer function
    vtkClipFilter->SetInputConnection(actor->GetMapper()->GetInputConnection(0, 0)->GetProducer()->GetOutputPort() );
    // could change source to actor->GetMapper()->GetInputConnection(0, 0)->GetProducer()
    // however becuase it is the inital filter it isn't exactly necessary

    vtkClipFilter->SetClipFunction( planeLeft.Get() );

    mapper->SetInputConnection(vtkClipFilter->GetOutputPort() );

    //actor = vtkSmartPointer<vtkActor>::New();

    actor->SetMapper(mapper);

    renderer->RemoveAllViewProps();
    renderer->AddActor(actor);
    renderWindow->Render();
  }

  if(applyShrink == true)
  {
    vtkSmartPointer<vtkShrinkFilter> shrinkFilter
                    = vtkSmartPointer<vtkShrinkFilter>::New();
    shrinkFilter->SetInputConnection(actor->GetMapper()->GetInputConnection(0, 0)->GetProducer()->GetOutputPort() );
    shrinkFilter->SetShrinkFactor(.8);
    shrinkFilter->Update();

    mapper->SetInputConnection(shrinkFilter->GetOutputPort() );

    actor->SetMapper(mapper);

    renderer->RemoveAllViewProps();
    renderer->AddActor(actor);
    renderWindow->Render();
  }


}


// Resets the camera of the model, both zoom and rotation of the model
// to  a default which can be set

void MainWindow::handleResetView()
{
  // New camera pointer is created
 // camera = vtkSmartPointer<vtkCamera>::New();

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
  ui->qvtkWidget->GetRenderWindow()->Render();
}

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
  vtkSmartPointer<vtkNamedColors> colors =
                  vtkSmartPointer<vtkNamedColors>::New();
  //vtkSmartPointer<vtkDataSetMapper>
  mapper = vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputData(ug);

//  vtkSmartPointer<vtkActor> actor =
  //    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->EdgeVisibilityOff();
  actor->GetProperty()->SetColor(colors->GetColor3d("Cyan").GetData());

  // clear old render and add new one

  renderer->RemoveAllViewProps();

  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

  // create a copy of the current source to be used with filters if necessary
  source = actor->GetMapper()->GetInputConnection(0, 0)->GetProducer();

  //---- reset the camera angle------
  camera = vtkSmartPointer<vtkCamera>::New();
  // 0,0,0 focal point is default when making new camera
  //camera->SetFocalPoint(0,0,0);
  renderer->SetActiveCamera(camera);
  renderer->ResetCamera(); // resets the zoom
  renderer->ResetCameraClippingRange(); // if the model is zoomed offscreen
  // /reset camera angle----------------
  // render the pyramid as soon as button is pushed
  renderWindow->Render();

  updateFilters();



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

  // Create an actor that is used to set the cube's properties for rendering
  // and place it in the window
//  vtkSmartPointer<vtkActor> actor =
  //                vtkSmartPointer<vtkActor>::New();

  actor->SetMapper(mapper);
  actor->GetProperty()->EdgeVisibilityOff();

  // code for colours
  vtkSmartPointer<vtkNamedColors> colors =
                  vtkSmartPointer<vtkNamedColors>::New();
  // colour of the object
  actor->GetProperty()->SetColor( colors->GetColor3d("Magenta").GetData() );

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground( colors->GetColor3d("Silver").GetData() );

  // create a copy of the current source to be used with filters if necessary
  source = actor->GetMapper()->GetInputConnection(0, 0)->GetProducer();

  //---- reset the camera angle------
  camera = vtkSmartPointer<vtkCamera>::New();
  // 0,0,0 focal point is default when making new camera
  camera->SetFocalPoint(1,-1,0);
  renderer->SetActiveCamera(camera);
  renderer->ResetCamera(); // resets the zoom
  renderer->ResetCameraClippingRange(); // if the model is zoomed offscreen
  // /reset camera angle----------------

  //  renderer->GetActiveCamera()->Azimuth(30);
  //  renderer->GetActiveCamera()->Elevation(30);



  // render the cube as soon as button is pushed
  renderWindow->Render();

  updateFilters();


}


// definitions of buttons

void MainWindow::actionOpen()
{
  // open file explorer

  QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"),
    "C:/",
  tr("STL Files (*.stl)"));

  // set file up with a reader
  std::string inputFilename = fileName.toLocal8Bit().constData();
  //std::string inputFilename = fileName;

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

  //actor 
/ vtkSmartPointer<vtkActor> actor2 =
                  vtkSmartPointer<vtkActor>::New();
   actor2->SetMapper(mapper); 

   renderWindow->AddRenderer(renderer); 

   //setup camera 
   renderer->AddActor(actor2); 

   //transformer 
   vtkSmartPointer<vtkTransform> transform =
	   vtkSmartPointer<vtkTransform>::New();
   transform->Translate(10.0, 20.0, 30.0);

   vtkSmartPointer<vtkAxesActor> axes =
	   vtkSmartPointer<vtkAxesActor>::New();  

   // The axes are positioned with a user transform
   axes->SetUserTransform(transform);
   axes->SetTotalLength(10, 10, 10);

   renderer->AddActor(axes);

   //colours 
  vtkSmartPointer<vtkNamedColors> colors =
                  vtkSmartPointer<vtkNamedColors>::New(); 

  

  // Setup the renderers's camera
  renderer->AddActor(actor);
  renderer->SetBackground( colors->GetColor3d("Silver").GetData()); // Background color green
  actor->GetProperty()->SetColor( colors->GetColor3d("Magenta").GetData() );

  // create a copy of the current source to be used with filters if necessary
  source = actor->GetMapper()->GetInputConnection(0, 0)->GetProducer();

  // Setup the renderers's camera
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCameraClippingRange();
  
  //renderWindowInteractor->Start();
  ui->qvtkWidget->GetRenderWindow()->Render(); 

  // Render the new model straight away
  renderWindow->Render();

  updateFilters();
}

<<<<<<< HEAD
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
void MainWindow::handleViewx()
{

	vtkSmartPointer<vtkCamera> camera2 = vtkSmartPointer<vtkCamera>::New();

	//renderer->SetActiveCamera(camera2);
	renderer->ResetCamera();
	camera2 = renderer->GetActiveCamera();



	camera2->SetPosition(0, 0, 1);
	camera2->SetFocalPoint(0, 0, 0);
	camera2->SetViewUp(0, 0, 0);

	// To view the full bounds of your scene
	renderer->ResetCamera();
	ui->qvtkWidget->GetRenderWindow()->Render();


}

void MainWindow::handleViewx2()
{

	vtkSmartPointer<vtkCamera> camera2 = vtkSmartPointer<vtkCamera>::New();

	//renderer->SetActiveCamera(camera2);
	renderer->ResetCamera();
	camera2 = renderer->GetActiveCamera();



	camera2->SetPosition(0, 0, -1);
	camera2->SetFocalPoint(0, 0, 0);
	camera2->SetViewUp(0, 0, 0);

	// To view the full bounds of your scene
	renderer->ResetCamera();
	ui->qvtkWidget->GetRenderWindow()->Render();


}


=======
>>>>>>> 4b0aaa701a9c6f2cfd3914b3ffb6d2a64c278bb4
