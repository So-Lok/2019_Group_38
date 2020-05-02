/**
* @file mainwindow.h
* Contains function declarations of the main window
*/


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

//Distance widget
#include <vtkDistanceWidget.h>
#include <vtkDistanceRepresentation.h>

//Axis widget
#include <vtkVersion.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>
#include <vtkPropAssembly.h>
#include <vtkSmartPointer.h>


namespace Ui {
class MainWindow;
}
/**
 * Sets up the maindwindow ui. Connects all mainwindow buttons to functions
 * sets up additional window(s) and initalises vtk variables
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // closeEvent
    /**
    *  Override of CloseEvent
    *  Used to terminate interactor if box widget is running whilst closing the program
    */
    void closeEvent(QCloseEvent *event);
    /**
    * Controls the box Wiget feature, allows user to alter size of model
    */
    void widgetBox();
    /**
    *  Allows the user to import a STL file into the renderer
    */
    void actionOpen();
    // model buttons

    /**
    *  Resets the camera of the render window to a preset position
    */
    void handleResetView();

    // display/render function, for use of filters.

    /**
    * Removes all active filters and reloads the current model to its' initial state
    */
    void resetFilter();
    /**
    * Handles the application of the clip filter
    * Clips a part of the model using preset values
    */
    void handleClip();
    /**
    * Handles the application of the shrink filter
    * Shrinks the model by a scaling factor
    */
    void handleShrink();



    /**
    * Handles the changing of the model's colour
    */
    void handleObjectColor();
    //Background color //
    /**
    * Handles the changing of the background's colour
    */
    void handleBackgroundColor();

    //Distance widget //
       /**
       * Handles the measuring of the distance if the check box has been checked
       */
    void handledistWid();

   //Axis label //
   /**
   * Handles the marking of axes on screen
   */
    void handleaxisLabel();

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
    // filter parameters
    //--------------Univessal-------------------
    bool filterApplied;
   /**
   *This parameter is for checking whether the distance widget checkbox has been check
   */
    bool applydist;
    // ------------------Clip Filter------------
     double clipOriginX = 0.0;  double clipNormalX = -1.0;
     double clipOriginY = 0.0;  double clipNormalY = 0.0;
     double clipOriginZ = 0.0;  double clipNormalZ = 0.0;
     //----------------------
     //-----------------Shrink Filter--------------
     double shrinkFactor = 0.8;
     //-----------------------------
    vtkSmartPointer<vtkRenderer> renderer;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;

    vtkSmartPointer<vtkDataSetMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkAlgorithm> source;

    vtkSmartPointer<vtkCamera> camera;

    vtkSmartPointer<vtkBoxWidget> boxWidget;
    vtkSmartPointer<vtkRenderWindowInteractor> interactor;

    vtkSmartPointer<vtkNamedColors> colors;
    vtkSmartPointer<vtkLight> light;

    /**
    *vtkDistanceWidget is used to measure the distance between two points.
    */
    vtkSmartPointer<vtkDistanceWidget> distanceWidget = vtkSmartPointer<vtkDistanceWidget>::New();

    /**
    *vtkAxesActor is a 2d/3d actor representing 3 dimension axes on the screen.
    */
    vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();

    /**
    *vtkOrientationMarkerWidget is for manipulating the position,size,orientaion of a prop that represent the orientaion marker.
    */
    vtkSmartPointer<vtkOrientationMarkerWidget> orientationWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
};

// call back used for box widget

/**
 *  Used to synchronise the box widget with the model
 *  so that it can be transformed
 */
class vtkMyCallback : public vtkCommand
{
public:
  static vtkMyCallback *New()
  {
    return new vtkMyCallback;
  }
  /**
  * Transforms the model
  */
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
