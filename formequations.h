#ifndef FORMEQUATIONS_H
#define FORMEQUATIONS_H

#include <QWidget>
#include <QKeyEvent>
#include <Qt>
#include <QDoubleSpinBox>

namespace Ui {
class FormEquations;
}

class FormEquations : public QWidget
{
    Q_OBJECT

public:
    explicit FormEquations(QWidget *parent = 0);
    ~FormEquations();

private slots:
    void on_pushButtonCalculate_clicked();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::FormEquations *ui;
    std::vector<QDoubleSpinBox *> dspbx;

};

#endif // FORMEQUATIONS_H
