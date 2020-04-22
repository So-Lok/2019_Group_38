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


    //object color////
    void handleObjectColor();

    //Background color //
    void handleBackgroundColor(); 

	//-X plane view bottom 
	void handleViewx();

	//-X plane view bottom
	void handleViewx2();


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
<<<<<<< HEAD

    //color
    vtkSmartPointer<vtkNamedColors> colors;

=======
   
>>>>>>> 4b0aaa701a9c6f2cfd3914b3ffb6d2a64c278bb4
};

 


#endif // MAINWINDOW_H