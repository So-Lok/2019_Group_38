#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
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
#include <QColorDialog>
#include <QColor>
#include <vtkClipDataSet.h>
#include <vtkShrinkFilter.h>
#include <vtkSTLReader.h>
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <vtkLight.h>


namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    vtkSmartPointer<vtkLight> light;
    vtkSmartPointer<vtkCubeSource> cubeSource;
    vtkSmartPointer<vtkSTLReader> reader;
    vtkSmartPointer<vtkDataSetMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkNamedColors> colors;
    vtkSmartPointer<vtkRenderer> renderer;

private slots:
    void on_actionFileOpen_triggered();
    void on_horizontalSlider_sliderMoved(int position);
    void on_turnOnOff_clicked(bool checked);
    void handleChangeModelColour();
    void handleChangeBackgroundColour();
    void on_clipFilter_clicked(bool checked);
    void on_shrinkFilter_clicked(bool checked);
    void filter_number(int CheckBoxname);
    void handleResetModelView();

private:
    Ui::MainWindow* ui;
    vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
    vtkSmartPointer<vtkShrinkFilter> shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
    vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();

};
#endif