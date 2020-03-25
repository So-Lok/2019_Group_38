#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkDataSetMapper.h>
// for use of reverse access to the source
#include <vtkAlgorithmOutput.h>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //shape buttons
    void handleCube();
    void handlePyrmaid();

    // actions
    void actionOpen();

    // model buttons
    void handleResetView();

    // display/render function, for use of filters.
    void updateFilters();

    // checkboxes
  //  void clipChecked();
  
  ;


private:
    Ui::MainWindow *ui;

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
   
};



#endif // MAINWINDOW_H
