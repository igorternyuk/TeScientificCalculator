#ifndef FORMDERIVATIVE_H
#define FORMDERIVATIVE_H

#include <QWidget>
#include <QLocale>
#include <QDoubleSpinBox>
#include <QKeyEvent>
#include <Qt>

namespace Ui {
class FormDerivative;
}

class FormDerivative : public QWidget
{
    Q_OBJECT

public:
    explicit FormDerivative(QWidget *parent = 0);
    ~FormDerivative();

private slots:
    void on_pushButtonCalculate_clicked();
    void on_pushButtonExit_clicked();
private:
    Ui::FormDerivative *ui;
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // FORMDERIVATIVE_H
