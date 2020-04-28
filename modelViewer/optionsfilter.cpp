#include "optionsfilter.h"
#include "ui_optionsfilter.h"
#include <QAbstractSlider>

optionsFilter::optionsFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::optionsFilter)
{
    ui->setupUi(this);

    //connect(ui->clipOriginX, &QAbstractSlider::valueChanged, this, &optionsFilter::getSliderValue);



}

optionsFilter::~optionsFilter()
{
    delete ui;
}
/*
void  optionsFilter::getSliderValue()
{
  int value = ui->clipOriginX->value();
  emit sendClipOriginX(value);
}
*/
void optionsFilter::on_clipOriginX_valueChanged(int value)
{
  ui->clipOriginX->setValue(value);
  int sendClip = value;
  emit sendClipOriginX(sendClip);
}
