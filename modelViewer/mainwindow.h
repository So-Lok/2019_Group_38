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
<<<<<<< Updated upstream
=======
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

     /** 
      * methods handle the different camera views buttons 
      */
      
       // X plane view bottom 
	void handleViewx();

       // -X plane view bottom
	void handleViewx2(); 
       
       // Y plane view bottom 
         void handleViewy(); 
        
       // -Y plane view bottom 
         void handleViewy2(); 
 
       // Z plane view bottom 
         void handleViewz(); 
 
       // -Z plane view bottom  
        
         void handleViewz2(); 
		// 90 degrees switcher button
		 void handleView90(); 
		// -90 degrees switcher button
		 void handleView902();

private slots:
    /**
    * 
    */
    void on_Slider_sliderMoved(int position);
    void on_checkBox_clicked(bool checked);

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


>>>>>>> Stashed changes

    //Background color //
    void handleBackgroundColor(); 

	//-X plane view bottom 
	void handleViewx();

	//-X plane view bottom
	void handleViewx2(); 
       
        //Y plane view bottom 
         void handleViewy(); 
        
        //-Y plane view bottom 
         void handleViewy2(); 
 
        //Z plane view bottom 
         void handleViewz(); 
 
        //-Z plane view bottom 
         void handleViewz2(); 
       
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
