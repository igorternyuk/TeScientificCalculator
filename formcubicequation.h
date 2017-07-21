#ifndef FORMCUBICEQUATION_H
#define FORMCUBICEQUATION_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QKeyEvent>
#include <Qt>
#include <vector>

namespace Ui {
class FormCubicEquation;
}

class FormCubicEquation : public QWidget
{
    Q_OBJECT

public:
    explicit FormCubicEquation(QWidget *parent = 0);
    ~FormCubicEquation();

private slots:
    void on_pushButtonCalculate_clicked();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::FormCubicEquation *ui;
    std::vector<QDoubleSpinBox*> dspbx;
};

#endif // FORMCUBICEQUATION_H
