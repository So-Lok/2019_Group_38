#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QMainWindow>
#include <QColorDialog>
#include <QColor>
#include <vtkLight.h>
#include <vtkPlane.h>
#include <vtkSTLReader.h>
#include <vtkShrinkFilter.h>
#include <vtkClipDataSet.h>
#include <vtkSTLReader.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    vtkSmartPointer<vtkDataSetMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkNamedColors> colors;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkLight> light;
    vtkSmartPointer<vtkSTLReader> reader;
 
    
   

private slots:

    void on_actionFileOpen_triggered();
    void handleObjectColor();
    void handleBackgroundColor();
    void on_Slider_sliderMoved(int position);
    void on_checkBox_clicked(bool checked);
    void handleResetCamera();
    void on_clipfilter_clicked(bool checked);
    void on_shrinkfilter_clicked(bool checked);
    

private:

    Ui::MainWindow* ui; 
    vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
    vtkSmartPointer<vtkClipDataSet> clipfilter = vtkSmartPointer<vtkClipDataSet>::New();
    vtkSmartPointer<vtkShrinkFilter> shrinkfilter = vtkSmartPointer<vtkShrinkFilter>::New();
   
};
   



#endif // MAINWINDOW_H
