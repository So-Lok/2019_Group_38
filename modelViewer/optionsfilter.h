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

private:
    Ui::optionsFilter *ui;
};

#endif // OPTIONSFILTER_H
