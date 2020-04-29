#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkDataSetMapper.h>
// for use of reverse access to the source
#include <vtkAlgorithmOutput.h>

///color//
#include <QColorDialog>
#include <QColor>
#include <vtkNamedColors.h>
//light//
#include <vtkLight.h>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


   
private slots:

    void on_Slider_sliderMoved(int position);
    void on_checkBox_clicked(bool checked);
    void on_EdgeCheckBox_toggled(bool checked);

    //shape buttons
    void handleCube();
    void handlePyrmaid();
    // actions
    void actionOpen();
    // model buttons
    void handleResetView();
    // display/render function, for use of filters.
    void updateFilters();
    //object color////
    void handleObjectColor();
    //Background color //
    void handleBackgroundColor();
  

 
private:
    Ui::MainWindow* ui;

    // filter boolean
    bool applyClip;
    bool applyShrink;

    // vtkSmartPointer definitions

    vtkSmartPointer<vtkRenderer> renderer;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    // test using this for filters
    vtkSmartPointer<vtkDataSetMapper> mapper;
    // actionOpen uses vtkPolyDataMapper,

    // to retain default propertie e.g colour
    vtkSmartPointer<vtkActor> actor;
    // for default camera
    vtkSmartPointer<vtkCamera> camera;
    // to store a copy of the current sourrce
    vtkSmartPointer<vtkAlgorithm> source;
    //color
    vtkSmartPointer<vtkNamedColors> colors;
    //light
    vtkSmartPointer<vtkLight> light;


   
};



#endif // MAINWINDOW_H
