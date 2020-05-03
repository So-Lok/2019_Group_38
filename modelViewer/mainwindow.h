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
    explicit MainWindow(QWidget* parent = 0);
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





private slots:


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

    //light intensity//
    /**
    * handles the sliding of the light intensity after checked the ON/OFF box
    */
    void on_Slider_sliderMoved(int position);
    /**
   * handles the ON/OFF box of the light intensity sliding 
   */
    void on_checkBox_clicked(bool checked);

    //Edge//
    /**
   * handles the edge when checked the box 
   */
    void on_EdgeCheckBox_toggled(bool checked);


    // Advanced filter options

    /**
    * This function displays the edit filters dialog
    */
    void on_editFilters_clicked();
    //----------- Clip Filter--------------
    /**
    * This handles the value received from the signal emitted from the edit filters window for clipOriginX
    * @param value equals to the slider value changed in the edit filters window
    */
    void updateClipOriginX(int value);
    /**
    * This handles the value received from the signal emitted from the edit filters window for clipNormalX
    * @param value equals to the slider value changed in the edit filters window
    */
    void updateClipNormalX(int value);
    /**
    * This handles the value received from the signal emitted from the edit filters window for clipOriginY
    * @param value equals to the slider value changed in the edit filters window
    */
    void updateClipOriginY(int value);
    /**
    * This handles the value received from the signal emitted from the edit filters window for clipNormalY
    * @param value equals to the slider value changed in the edit filters window
    */
    void updateClipNormalY(int value);
    /**
    * This handles the value received from the signal emitted from the edit filters window for clipOriginZ
    * @param value equals to the slider value changed in the edit filters window
    */
    void updateClipOriginZ(int value);
    /**
    * This handles the value received from the signal emitted from the edit filters window for clipNormalZ
    * @param value equals to the slider value changed in the edit filters window
    */
    void updateClipNormalZ(int value);
    //-------------------------------------

    //------------Shrink Filter--------
    /**
    * This handles the value received from the signal emitted from the edit filters window for shrinkFactor
    * @param value equals to the slider value changed in the edit filters window
    */
    void updateShrinkFactor(int value);




private:
    Ui::MainWindow* ui;


    optionsFilter *opFilterDialog; ///< dialog class pointer for creation of the edit filters window

    bool applydist; ///< This parameter is for checking whether the distance widget checkbox has been check
    // ------------------Clip Filter------------
    double clipOriginX = 0.0; ///< X value of the origin for the clip filter, 0.0 is initial value
    double clipNormalX = -1.0; ///< X value of the normal for the clip filter, -1.0 is initial value
    double clipOriginY = 0.0; ///< Y value of the origin for the clip filter, 0.0 is initial value
    double clipNormalY = 0.0; ///< Y value of the normal for the clip filter, 0.0 is initial value
    double clipOriginZ = 0.0; ///< Z value of the origin for the clip filter, 0.0 is initial value
    double clipNormalZ = 0.0; ///< Z value of the normal for the clip filter, 0.0 is initial value
    //----------------------
    //-----------------Shrink Filter--------------
    double shrinkFactor = 0.8; ///< scale factor to shrink the model by for the shrink filter, 0.8 is the initial value
    //-----------------------------
    vtkSmartPointer<vtkRenderer> renderer;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;

    vtkSmartPointer<vtkDataSetMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkAlgorithm> source;

    vtkSmartPointer<vtkCamera> camera;

    vtkSmartPointer<vtkBoxWidget> boxWidget;
    vtkSmartPointer<vtkRenderWindowInteractor> interactor;

    /**
   *vtkNamedColors is used to change the color of the objects
   */
    vtkSmartPointer<vtkNamedColors> colors;
    /**
   *vtkLight is used to show the light intensity
   */
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
