#ifndef FORMINTEGRAL_H
#define FORMINTEGRAL_H

#include <QWidget>
#include <QKeyEvent>
#include <Qt>
#include <QDoubleSpinBox>

namespace Ui {
class FormIntegral;
}

class FormIntegral : public QWidget
{
    Q_OBJECT

public:
    explicit FormIntegral(QWidget *parent = 0);
    ~FormIntegral();

private slots:
    void on_pushButtonCalculate_clicked();
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::FormIntegral *ui;
    std::vector<QDoubleSpinBox *> qdspbx;
};

#endif // FORMINTEGRAL_H
