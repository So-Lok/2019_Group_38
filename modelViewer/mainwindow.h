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

// Box widget
#include <vtkBoxWidget.h>
#include <vtkCommand.h>
#include <vtkTransform.h>

// close event
#include <QCloseEvent>
#include <QMessageBox>

// Additonal windows
#include "optionsfilter.h"





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // closeEvent
    void closeEvent(QCloseEvent *event);
    //shape buttons
    void handleCube();
    void handlePyrmaid();
    // Tool bar functions
    void widgetBox();
    void actionOpen();
    // model buttons

    /**
    * @function resets the camera of the render window so that the model is on screen
    **/
    void handleResetView();

    // display/render function, for use of filters.
    void updateFilters();
    void resetFilter();
    // update filters will be changed as multiple filters cause problems
    // will check which box is ticked and then call handle functions
    void handleClip();
    void handleShrink();



    //object color////
    void handleObjectColor();
    //Background color //
    void handleBackgroundColor();

private slots:
    void on_Slider_sliderMoved(int position);
    void on_checkBox_clicked(bool checked);

    // Advanced filter options
    void on_editFilters_clicked();
    //----------- Clip Filter--------------
    void updateClipOriginX(int value); void updateClipNormalX(int value);
    void updateClipOriginY(int value); void updateClipNormalY(int value);
    void updateClipOriginZ(int value); void updateClipNormalZ(int value);
    //-------------------------------------
    //------------Shrink Filter--------
    void updateShrinkFactor(int value);



private:
    Ui::MainWindow* ui;

    optionsFilter *opFilterDialog;

    // filter boolean
  //  bool applyClip;
  //  bool applyShrink;

    // filter parameters
    // ------------------Clip Filter------------
     double clipOriginX = 0.0;  double clipNormalX = -1.0;
     double clipOriginY = 0.0;  double clipNormalY = 0.0;
     double clipOriginZ = 0.0;  double clipNormalZ = 0.0;
     //----------------------
     //-----------------Shrink Filter--------------
     double shrinkFactor = 0.8;
     //-----------------------------

    // vtkSmartPointer definitions

    vtkSmartPointer<vtkRenderer> renderer;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkDataSetMapper> mapper;
    // actionOpen uses vtkPolyDataMapper,

    // to retain default propertie e.g colour
    vtkSmartPointer<vtkActor> actor;
    // for default camera
    vtkSmartPointer<vtkCamera> camera;
    // to store a copy of the current sourrce
    vtkSmartPointer<vtkAlgorithm> source;
    vtkSmartPointer<vtkAlgorithm> currentModel;

    //color
    vtkSmartPointer<vtkNamedColors> colors;
    //light
    vtkSmartPointer<vtkLight> light;

    vtkSmartPointer<vtkBoxWidget> boxWidget;
    vtkSmartPointer<vtkRenderWindowInteractor> interactor;


};

// call back used for box widget

/**
 *  A callback class used to synchronise the box widget with the object
 *  so that it can be transformed
 *
 */

class vtkMyCallback : public vtkCommand
{
public:
  static vtkMyCallback *New()
  {
    return new vtkMyCallback;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSmartPointer<vtkTransform> t =
              vtkSmartPointer<vtkTransform>::New();
    vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
    widget->GetTransform(t);
    widget->GetProp3D()->SetUserTransform(t);
  }
};

#endif // MAINWINDOW_H
