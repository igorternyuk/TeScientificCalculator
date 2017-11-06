#ifndef FORMCUBICEQUATION_H
#define FORMCUBICEQUATION_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QKeyEvent>
#include <Qt>
#include <vector>

namespace Ui
{
    class FormCubicEquation;
}

class FormCubicEquation : public QWidget
{
    Q_OBJECT

public:
    explicit FormCubicEquation(QWidget *parent = nullptr);
    ~FormCubicEquation();


protected:
    void keyReleaseEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent*) override;

private slots:
    void on_pushButtonCalculate_clicked();
    void on_pushButtonExit_clicked();

private:
    Ui::FormCubicEquation *ui;
    std::vector<QDoubleSpinBox*> dspbx;
};

#endif // FORMCUBICEQUATION_H
