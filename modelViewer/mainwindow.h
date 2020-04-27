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
    void handleResetView();
    // display/render function, for use of filters.
    void updateFilters();

    //object color////
    void handleObjectColor();
    //Background color //
    void handleBackgroundColor();

private slots:
    void on_Slider_sliderMoved(int position);
    void on_checkBox_clicked(bool checked);

    // Advanced filter options
    void on_editFilters_clicked();

private:
    Ui::MainWindow* ui;

    optionsFilter *opFilterDialog;

    // filter boolean
    bool applyClip;
    bool applyShrink;

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
