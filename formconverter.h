#ifndef FORMCONVERTER_H
#define FORMCONVERTER_H

#include <QWidget>
#include <QKeyEvent>
#include <vector>
#include <QDoubleSpinBox>
#include <Qt>

namespace Ui {
class FormConverter;
}

class FormConverter : public QWidget
{
    Q_OBJECT

public:
    explicit FormConverter(QWidget *parent = 0);
    ~FormConverter();

private slots:
    void on_pushButtonConvert_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonAreaConvert_clicked();
    void on_pushButtonAreaClose_clicked();
    void on_pushButtonVolumeUnitsConvert_clicked();
    void on_pushButtonVolumeClose_clicked();
    void on_pushButtonSpeedConvert_clicked();
    void on_pushButtonSpeedClose_clicked();
    void on_pushButtonTemperatureConvert_clicked();
    void on_pushButtonTemperatureClose_clicked();
    void on_pushButtonPressureConvert_clicked();
    void on_pushButtonMassConvert_clicked();
    void on_pushButtonPressureClose_clicked();
    void on_pushButtonMassClose_clicked();
protected:
    void keyPressEvent(QKeyEvent *event);
    std::vector<QDoubleSpinBox*> dspbx;

private:
    Ui::FormConverter *ui;
};

#endif // FORMCONVERTER_H
