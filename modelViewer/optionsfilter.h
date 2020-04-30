#ifndef OPTIONSFILTER_H
#define OPTIONSFILTER_H

#include <QDialog>

namespace Ui {
class optionsFilter;
}

class optionsFilter : public QDialog
{
    Q_OBJECT

public:
    explicit optionsFilter(QWidget *parent = nullptr);
    ~optionsFilter();

// SLOTs for interactions
private slots:
    // --------------Clip Filter------------------------
    void on_clipOriginX_valueChanged(int value); void on_clipNormalX_valueChanged(int value);
    void on_clipOriginY_valueChanged(int value); void on_clipNormalY_valueChanged(int value);
    void on_clipOriginZ_valueChanged(int value); void on_clipNormalZ_valueChanged(int value);
    // ------------------------------------------------

    // -------shrink filter------
    void on_shrinkFactor_valueChanged(int value);
    //---------------------------

// SIGNALS to the MainWindow
signals:
    // --------------Clip Filter---------------
    void sendClipOriginX(int value); void sendClipNormalX(int value);
    void sendClipOriginY(int value); void sendClipNormalY(int value);
    void sendClipOriginZ(int value); void sendClipNormalZ(int value);
    // -------------------------------------------
    // ------------shrink filter ------
    void sendShrinkFactor(int value);
    //-------------------------

private:
    Ui::optionsFilter *ui;
};

#endif // OPTIONSFILTER_H
