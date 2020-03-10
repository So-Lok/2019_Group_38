#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QFileDialog>
#include <vtkSTLReader.h>
#include <QColorDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vtkPolyDataMapper.h>
#include <vtkLight.h>
#include <vtkPlane.h>
#include <vtkClipDataSet.h>





MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	// standard call to setup Qt UI (same as previously)
	ui->setupUi(this);


	connect(ui->ObjectColor, &QPushButton::released, this, &MainWindow::handleObjectColor);
	connect(ui->BackgroundColor, &QPushButton::released, this, &MainWindow::handleBackgroundColor);
	connect(ui->ResetCamera, &QPushButton::released, this, &MainWindow::handleResetCamera);

	// Now need to create a VTK render window and link it to the QtVTK widget
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	ui->qvtkWidget->SetRenderWindow(renderWindow);			// note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt creator

	// Now use the VTK libraries to render something. To start with you can copy-paste the cube example code, there are comments to show where the code must be modified.
	//--------------------------------------------- Code From Example 1 --------------------------------------------------------------------------

	//choosing file by ourself
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "./", tr("STL Files(*.stl)"));
	std::string str = fileName.toUtf8().constData();
	reader = vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName(str.data());
	reader->Update();

	mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());

	// Create an actor that is used to set the cube's properties for rendering and place it in the window
	actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->EdgeVisibilityOn();

	colors = vtkSmartPointer<vtkNamedColors>::New();
	actor->GetProperty()->SetColor(colors->GetColor3d("Blue").GetData());

	// Create a renderer, and render window
	renderer = vtkSmartPointer<vtkRenderer>::New();
	//vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();		// ###### We've already created the renderWindow this time ######
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);									// ###### ask the QtVTKOpenGLWidget for its renderWindow ######

	// Link a renderWindowInteractor to the renderer (this allows you to capture mouse movements etc)  ###### Not needed with Qt ######
	//vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	//renderWindowInteractor->SetRenderWindow( ui->vtkWidget->GetRenderWindow() );	

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
	renderer->AddActor(actor);
	renderer->AddLight(light);
	renderer->SetBackground(colors->GetColor3d("Silver").GetData());
	
	// Setup the renderers's camera
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Azimuth(30);
	renderer->GetActiveCamera()->Elevation(30);
	renderer->ResetCameraClippingRange();

	// Render and interact
	//renderWindow->Render();					// ###### Not needed with Qt ######
	//renderWindowInteractor->Start();			// ###### Not needed with Qt ######
	//--------------------------------------------- /Code From Example 1 -------------------------------------------------------------------------*/
}
void MainWindow::on_actionFileOpen_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "./", tr("STL Files(*.stl)"));
	std::string str = fileName.toUtf8().constData();
	reader->SetFileName(str.data());
	reader->Update();
	renderer->ResetCamera();
	ui->qvtkWidget->GetRenderWindow()->Render();
}


/////////////////objectcolor///////

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
////////////////////slide of light intensity ////////////////

void MainWindow::on_Slider_sliderMoved(int position)
{
	if (ui->checkBox->isChecked()) {
		light->SetIntensity((float)(100 - position) / 100);
	}
	else {
		light->SetIntensity(1);
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
		light->SetIntensity(1);
	}
	ui->qvtkWidget->GetRenderWindow()->Render();
}

////clip filter ///

void MainWindow::on_clipfilter_clicked(bool checked)
{
	if (checked) {

		planeLeft->SetOrigin(0.0, 0.0, 0.0);
		planeLeft->SetNormal(-1.0, 0.0, 0.0);
		clipfilter->SetInputConnection(reader->GetOutputPort());
		clipfilter->SetClipFunction(planeLeft.Get());
		mapper->SetInputConnection(clipfilter->GetOutputPort());
	}

	ui->qvtkWidget->GetRenderWindow()->Render();
}

////shrink fliter ///

void MainWindow::on_shrinkfilter_clicked(bool checked)
{
	if (checked) {

		shrinkfilter->SetInputConnection(reader->GetOutputPort());
		shrinkfilter->SetShrinkFactor(.8);
		shrinkfilter->Update();
		mapper->SetInputConnection(shrinkfilter->GetOutputPort());
		
	}
	ui->qvtkWidget->GetRenderWindow()->Render();
}


///////////////Reset////////////////////

void MainWindow::handleResetCamera()
{
	renderer->ResetCamera();
	mapper->SetInputConnection(reader->GetOutputPort());
	
	//light->SetIntensity(1);

	ui->qvtkWidget->GetRenderWindow()->Render();
}


MainWindow::~MainWindow()
{
	delete ui;
}


