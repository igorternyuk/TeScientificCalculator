#ifndef FORMEQUATIONS_H
#define FORMEQUATIONS_H

#include <QWidget>
#include <QKeyEvent>
#include <Qt>
#include <QDoubleSpinBox>

namespace Ui
{
    class FormEquations;
}

class FormEquations : public QWidget
{
    Q_OBJECT

public:
    explicit FormEquations(QWidget *parent = nullptr);
    ~FormEquations();

protected:
    void keyReleaseEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent*) override;

private slots:
    void on_pushButtonCalculate_clicked();

    void on_pushButton_clicked();

private:
    Ui::FormEquations *ui;
    std::vector<QDoubleSpinBox *> dspbx;

};

#endif // FORMEQUATIONS_H
