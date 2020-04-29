#include "optionsfilter.h"
#include "ui_optionsfilter.h"

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
