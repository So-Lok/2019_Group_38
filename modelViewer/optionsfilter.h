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

    //void getSliderValue();
private slots:
    void on_clipOriginX_valueChanged(int value);


// signals for mainWindow to receive
signals:
    void sendClipOriginX(int value);

private:
    Ui::optionsFilter *ui;
};

#endif // OPTIONSFILTER_H
