/**
* @file optionsfilter.h
*  @brief This file contains all of the function declarations for the edit filters window
*
*/


#ifndef OPTIONSFILTER_H
#define OPTIONSFILTER_H

#include <QDialog>

namespace Ui {
class optionsFilter;
}
/**
* This is the class of the edit filters window, it inherits public functions of QDialog
*/
class optionsFilter : public QDialog
{
    Q_OBJECT

public:
    explicit optionsFilter(QWidget *parent = nullptr);
    ~optionsFilter();

// SLOTs for interactions
private slots:
   /**
    * This fucntions emits a signal to the maindwindow when the slider clipOriginX is changed
    */
    void on_clipOriginX_valueChanged(int value);
   /**
    * This fucntions emits a signal to the maindwindow when the slider clipNormalX is changed
    */
    void on_clipNormalX_valueChanged(int value);
   /**
    * This fucntions emits a signal to the maindwindow when the slider clipOriginY is changed
    */
    void on_clipOriginY_valueChanged(int value);
   /**
    * This fucntions emits a signal to the maindwindow when the slider clipNormalY is changed
    */
    void on_clipNormalY_valueChanged(int value);
   /**
    * This fucntions emits a signal to the maindwindow when the slider clipOriginZ is changed
    */
    void on_clipOriginZ_valueChanged(int value);
   /**
    * This fucntions emits a signal to the maindwindow when the slider clipNormalZ is changed
    */
    void on_clipNormalZ_valueChanged(int value);

   /**
    * This fucntions emits a signal to the maindwindow when the slider shrinkFactor is changed
    */
    void on_shrinkFactor_valueChanged(int value);
    //---------------------------

// SIGNALS
signals:
    /**
    * SIGNAL to mainwindow containing value changed on slider for clipOriginX
    */
    void sendClipOriginX(int value);
    /**
    * SIGNAL to mainwindow containing value changed on slider for clipNormalX
    */
    void sendClipNormalX(int value);
    /**
    * SIGNAL to mainwindow containing value changed on slider for clipOriginY
    */
    void sendClipOriginY(int value);
    /**
    * SIGNAL to mainwindow containing value changed on slider for clipNormalY
    */
    void sendClipNormalY(int value);
    /**
    * SIGNAL to mainwindow containing value changed on slider for clipOriginZ
    */
    void sendClipOriginZ(int value);
    /**
    * SIGNAL to mainwindow containing value changed on slider for clipNormalZ
    */
    void sendClipNormalZ(int value);

    /**
    * SIGNAL to mainwindow containing value changed on slider for shrinkFactor
    */
    void sendShrinkFactor(int value);
    //-------------------------

private:
    Ui::optionsFilter *ui;
};

#endif // OPTIONSFILTER_H
