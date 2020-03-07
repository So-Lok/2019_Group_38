#include <vtkSmartPointer.h>
//#include <vtkCubeSource.h>
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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <vtkSTLReader.h>
#include <vtkClipDataSet.h>
#include <vtkPlane.h>
#include <vtkLight.h>
#include <vtkPolyDataMapper.h>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // standard call to setup Qt UI 
    ui->setupUi(this);

    //all push buttons
    connect(ui->ChangeModelColour, &QPushButton::released, this, &MainWindow::handleChangeModelColour);
    connect(ui->ChangeBackgroundColour, &QPushButton::released, this, &MainWindow::handleChangeBackgroundColour);
    connect(ui->ResetModelView, &QPushButton::released, this, &MainWindow::handleResetModelView);

    // Now need to create a VTK render window and link it to the QtVTK widget
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    // creator
    ui->qvtkWidget->SetRenderWindow(renderWindow);

    //Open file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "./", tr("STL Files(*.stl)"));
    std::string str = fileName.toUtf8().constData();
    reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(str.data());
    reader->Update();


    // Create a mapper that will hold the shape's geometry in a format suitable for rendering
    mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputConnection(reader->GetOutputPort());

    // Create an actor that is used to set the 's properties for rendering
    actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->EdgeVisibilityOn();

    colors = vtkSmartPointer<vtkNamedColors>::New();
    actor->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());

    // Create a renderer, and render window
    renderer = vtkSmartPointer<vtkRenderer>::New();
    ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer); // ###### ask the QtVTKOpenGLWidget for its renderWindow ######

    // Link a renderWindowInteractor to the renderer (this allows you to capture mouse movements etc)  ###### Not needed with Qt ######  
    light = vtkSmartPointer<vtkLight>::New();
    light->SetLightTypeToSceneLight();
    //light->SetLightTypeToHeadlight();
    light->SetPosition(5, 5, 15);
    light->SetPositional(true);
    light->SetConeAngle(10);
    light->SetFocalPoint(0, 0, 0);
    light->SetDiffuseColor(1, 1, 1);
    light->SetAmbientColor(1, 1, 1);
    light->SetSpecularColor(1, 1, 1);
    light->SetIntensity(0.5);


    // Add the actor and light to the scene
    renderer->AddActor(actor);
    renderer->SetBackground(colors->GetColor3d("Silver").GetData());
    renderer->AddLight(light);

    // Setup the renderers's camera
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();



}

MainWindow::~MainWindow()
{
    delete ui;
}

//clip filter
void MainWindow::on_clipFilter_clicked(bool checked)
{
    if (checked) {

        planeLeft->SetOrigin(0.0, 0.0, 0.0);
        planeLeft->SetNormal(-1.0, 0.0, 0.0);
        clipFilter->SetInputConnection(reader->GetOutputPort());
        clipFilter->SetClipFunction(planeLeft.Get());
        mapper->SetInputConnection(clipFilter->GetOutputPort());
        filter_number(1);

    }
    ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_actionFileOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "../../stl", tr("STL Files(*.stl)"));
    std::string str = fileName.toUtf8().constData();
    reader->SetFileName(str.data());
    reader->Update();
    renderer->ResetCamera();
    ui->qvtkWidget->GetRenderWindow()->Render();
}

//shrinkfilter
void MainWindow::on_shrinkFilter_clicked(bool checked)
{
    if (checked) {

        shrinkFilter->SetInputConnection(reader->GetOutputPort());
        shrinkFilter->SetShrinkFactor(.8);
        shrinkFilter->Update();
        mapper->SetInputConnection(shrinkFilter->GetOutputPort());
        filter_number(2);

    }
    ui->qvtkWidget->GetRenderWindow()->Render();
}
//reset view
void MainWindow::handleResetModelView()
{
    renderer->ResetCamera();
    mapper->SetInputConnection(reader->GetOutputPort());
    filter_number(3);
    //light->SetIntensity(0.5);

    ui->qvtkWidget->GetRenderWindow()->Render();
}
//apply filter select just one
void MainWindow::filter_number(int numeberCheckbox)
{
    switch (numeberCheckbox)
    {

    case 1: ui->shrinkFilter->setChecked(false);
        break;
    case 2: ui->clipFilter->setChecked(false);
        break;
    case 3: ui->clipFilter->setChecked(false);
        ui->shrinkFilter->setChecked(false);
        ui->turnOnOff->setChecked(false);
        light->SetIntensity(0.5);
        break;

    }
}
//change object color
void MainWindow::handleChangeModelColour()
{
    QColor QTcolor = QColorDialog::getColor(Qt::white, this);
    if (QTcolor.isValid())
    {
        actor->GetProperty()->SetColor(QTcolor.redF(), QTcolor.greenF(), QTcolor.blueF());
        ui->qvtkWidget->GetRenderWindow()->Render();
    }
}
//light intensity with turn off/on and adjust intensity 
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    if (ui->turnOnOff->isChecked()) {
        light->SetIntensity((float)(100 - position) / 100);
    }
    else {
        light->SetIntensity(0.5);
    }
    ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_turnOnOff_clicked(bool checked)
{
    if (checked) {
        light->SetIntensity((float)(100 - ui->horizontalSlider->value()) / 100);
    }
    else {
        light->SetIntensity(0.5);
    }
    ui->qvtkWidget->GetRenderWindow()->Render();
}
//background color
void MainWindow::handleChangeBackgroundColour()
{
    QColor QTcolor = QColorDialog::getColor(Qt::white, this);
    if (QTcolor.isValid())
    {
        renderer->SetBackground(QTcolor.redF(), QTcolor.greenF(), QTcolor.blueF());
        ui->qvtkWidget->GetRenderWindow()->Render();
    }
}