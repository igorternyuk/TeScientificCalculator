#ifndef FORMINTEGRAL_H
#define FORMINTEGRAL_H

#include <QWidget>
#include <QKeyEvent>
#include <Qt>
#include <QDoubleSpinBox>

namespace Ui
{
    class FormIntegral;
}

class FormIntegral : public QWidget
{
    Q_OBJECT

public:
    explicit FormIntegral(QWidget *parent = nullptr);
    ~FormIntegral();

private slots:
    void on_pushButtonCalculate_clicked();
    void on_pushButtonClose_clicked();

protected:
    void keyReleaseEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent*) override;

private:
    Ui::FormIntegral *ui;
    std::vector<QDoubleSpinBox *> qdspbx;
};

#endif // FORMINTEGRAL_H
