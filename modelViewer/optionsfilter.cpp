#include "optionsfilter.h"
#include "ui_optionsfilter.h"
#include <QAbstractSlider>

optionsFilter::optionsFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::optionsFilter)
{
    ui->setupUi(this);
}

optionsFilter::~optionsFilter()
{
    delete ui;
}

// --------------------Clip Filter -------------------------

void optionsFilter::on_clipOriginX_valueChanged(int value)
{
  ui->clipOriginX->setValue(value);
  int sendClip = value;
  emit sendClipOriginX(sendClip);
}

void optionsFilter::on_clipOriginY_valueChanged(int value)
{
  ui->clipOriginY->setValue(value);
  int sendClip = value;
  emit sendClipOriginY(sendClip);
}

void optionsFilter::on_clipOriginZ_valueChanged(int value)
{
  ui->clipOriginZ->setValue(value);
  int sendClip = value;
  emit sendClipOriginZ(sendClip);
}

void optionsFilter::on_clipNormalX_valueChanged(int value)
{
  ui->clipNormalX->setValue(value);
  int sendClip = value;
  emit sendClipNormalX(sendClip);
}

void optionsFilter::on_clipNormalY_valueChanged(int value)
{
  ui->clipNormalY->setValue(value);
  int sendClip = value;
  emit sendClipNormalY(sendClip);
}

void optionsFilter::on_clipNormalZ_valueChanged(int value)
{
  ui->clipNormalZ->setValue(value);
  int sendClip = value;
  emit sendClipNormalZ(sendClip);
}

// ----------------------------Clip Filter--------------------------------

void optionsFilter::on_shrinkFactor_valueChanged(int value)
{
    ui->shrinkFactor->setValue(value);
    emit sendShrinkFactor(value);
}
