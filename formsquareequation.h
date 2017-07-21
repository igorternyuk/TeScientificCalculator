#ifndef FORMSQUAREEQUATION_H
#define FORMSQUAREEQUATION_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QKeyEvent>
#include <Qt>
namespace Ui {
class FormSquareEquation;
}

class FormSquareEquation : public QWidget
{
    Q_OBJECT

public:
    explicit FormSquareEquation(QWidget *parent = 0);
    ~FormSquareEquation();

private slots:
    void on_pushButtonCalculate_clicked();
    void on_pushButtonClose_clicked();
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::FormSquareEquation *ui;
    std::vector<QDoubleSpinBox*> dspbx;

};

#endif // FORMSQUAREEQUATION_H
