#include "formconverter.h"
#include "ui_formconverter.h"
#include <math.h>
#include <QDoubleValidator>
#include <QCloseEvent>

FormConverter::FormConverter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormConverter)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    dspbx.push_back(ui->doubleSpinBoxDistanceInput);
    dspbx.push_back(ui->doubleSpinBoxAreaInput);
    dspbx.push_back(ui->doubleSpinBoxVolumeInput);
    dspbx.push_back(ui->doubleSpinBoxMassInput);
    dspbx.push_back(ui->doubleSpinBoxPressureInput);
    dspbx.push_back(ui->doubleSpinBoxTemperatureInput);
    dspbx.push_back(ui->doubleSpinBoxSpeedInput);
    QLocale locale(QLocale::English);
    for(auto &d: dspbx)
    {
        d->setLocale(locale);
        d->setMinimum(0.0);
        d->setMaximum(+99999999999.99999999);
        d->setSingleStep(1);
        d->setDecimals(4);
    }
}
FormConverter::~FormConverter()
{
    delete ui;
}

void FormConverter::closeEvent(QCloseEvent *)
{
    this->hide();
}

void FormConverter::on_pushButtonConvert_clicked()
{
    /*
     **Длина
     0 - нанометр 10^-9 m
     1 - микрон   10^-6 m
     2 - милиметр 10^-3 m
     3 - сантиметр 10^-2 m
     4 - дюйм      2.54 * 10^-2 m
     5 - дециметр 0.1 m
     6 - фут       30.48 * 10^-2m
     7 - ярд     91.44 * 10^-2 m
     8 - метр       1 m
     9 - кабельтов 185.2 m
     9 - километр 10^3 m
     10 - верста  1066.8 m
     11 - сухопутная миля 1609 m
     12 - морская миля 1852 m
    */
    double distance[] = {pow(10, -9), pow(10,-6), pow(10, -3), 0.01, 0.0254, 0.1,
                         0.3048, 0.9144, 1, 185.2, 1000, 1066.8, 1609, 1852};
    double inputValue = ui->doubleSpinBoxDistanceInput->value();
    double inputValueToMeters = distance[ui->comboBoxInputUnits->currentIndex()];
    inputValue *= inputValueToMeters;
    double outputValue = inputValue / distance[ui->comboBoxOutputUnits->currentIndex()];
    ui->lineEditOutput->setText(QString::number(outputValue, 'f', 10));
}
void FormConverter::on_pushButtonClose_clicked()
{
    this->hide();
}
void FormConverter::on_pushButtonAreaConvert_clicked()
{
    /*
     **Площадь
     0 - мм2              10^-6 m2
     1 - см2   10^-4 m2
     2 - кв.дюйм 2.54^2 * 10^-4 m2
     3 - дм2 0.01 m2
     4 - кв.фут  0.3048^2 m2
     5 - кв.ярд  0.9144^2 m2
     6 - м2       1 m2
     7 - сотка  100 m2
     8 - десятина 925.4 m2
     9 - акр 4046.86 m2
     10 - гектар 10000 m2
     11 - км2 1000000 m2
     12 - кв. сухопутная миля 1609^2 m
     13 - кв. морская миля 1852^2 m
    */
    double area[] = {pow(10, -6), pow(10,-4), pow(0.0254, 2), 0.01, pow(0.3048, 2), pow(0.9144, 2),
                         1.0, 100, 925.4, 4046.86, pow(10,4), pow(10,6), pow(1609,2), pow(1852,2)};
    double inputValue = ui->doubleSpinBoxAreaInput->value();
    double inputValueToSquareMeters = area[ui->comboBoxAreaInputUnits->currentIndex()];
    inputValue *= inputValueToSquareMeters;
    double outputValue = inputValue / area[ui->comboBoxAreaOutputUnits->currentIndex()];
    ui->lineEditAreaOutput->setText(QString::number(outputValue, 'f', 10));
}
void FormConverter::on_pushButtonAreaClose_clicked()
{
    on_pushButtonClose_clicked();
}
void FormConverter::on_pushButtonVolumeUnitsConvert_clicked()
{
    /*
     **Объем
     0 - мм3   10^-9 m3
     1 - см3   10^-6 m3
     2 - куб.дюйм 2.54^3 * 10^-6 m3
     3 - дм3 0.001 m3
     4 - куб.фут  0.3048^3 m3
     5 - куб.ярд  0.9144^3 m3
     6 - американская кварта 0.0009463 m3
     7 - литр     0.001 m3
     8 - английская имперская кварта 0.0011365 m3
     9 - американский галлон 0.00378541178 m3
     10 - английский галлон 0.004576 m3
     11 - баррель 0.158983 m3
     12 - м3       1 m2

    */
    double volume[] = {pow(10, -9), pow(10,-6), pow(0.0254, 3), 0.001, pow(0.3048, 3), pow(0.9144, 3),
                         0.0009463, 0.001, 0.0011365, 0.00378541178, 0.004576, 0.158983, 1.0};
    double inputValue = ui->doubleSpinBoxVolumeInput->value();
    double inputValueToCubicMeters = volume[ui->comboBoxVolumeInputUnits->currentIndex()];
    inputValue *= inputValueToCubicMeters;
    double outputValue = inputValue / volume[ui->comboBoxVolumeOutputUnits->currentIndex()];
    ui->lineEditVolumeOutput->setText(QString::number(outputValue, 'f', 10));
}
void FormConverter::on_pushButtonVolumeClose_clicked()
{
   on_pushButtonClose_clicked();
}
void FormConverter::on_pushButtonSpeedConvert_clicked()
{
    //Скорость
    /*
     м/с
     км/час
     км/с
     мили/час
     узлы
    */
    double speed[] = {1, pow(3.6,-1), 0.001, pow(3.6,-1)*1.609, pow(3.6,-1)*1.852};
    double inputValue = ui->doubleSpinBoxSpeedInput->value();
    double inputValueToMetersProSec = speed[ui->comboBoxSpeedInputUnits->currentIndex()];
    inputValue *= inputValueToMetersProSec;
    double outputValue = inputValue / speed[ui->comboBoxSpeedOutputUnits->currentIndex()];
    ui->lineEditSpeedOutput->setText(QString::number(outputValue, 'f', 10));
}
void FormConverter::on_pushButtonSpeedClose_clicked()
{
   on_pushButtonClose_clicked();
}
void FormConverter::on_pushButtonTemperatureConvert_clicked()
{
    /*
    Цельсий  t
    Кельвин  t + 273.15
    Френгейт (t - 32) * 5 / 9
   */
    double tempInCelsius;
    switch (ui->comboBoxTemperatureInputUnits->currentIndex()) {
        case 0: tempInCelsius = ui->doubleSpinBoxTemperatureInput->value(); break;
        case 1: tempInCelsius = ui->doubleSpinBoxTemperatureInput->value() - 273.15; break;
        case 2: tempInCelsius = (ui->doubleSpinBoxTemperatureInput->value() - 32) * 5 / 9; break;
    }
    switch (ui->comboBoxTemperatureOutputUnits->currentIndex()) {
        case 0: ui->lineEditTemperatureOutput->setText(QString::number(tempInCelsius, 'f', 6)); break;
        case 1: ui->lineEditTemperatureOutput->setText(QString::number(tempInCelsius + 273.15, 'f', 6)); break;
        case 2: ui->lineEditTemperatureOutput->setText(QString::number(tempInCelsius * 9 / 5 + 32, 'f', 6)); break;
    }
}
void FormConverter::on_pushButtonTemperatureClose_clicked()
{
    on_pushButtonClose_clicked();
}
void FormConverter::on_pushButtonPressureConvert_clicked()
{
    /*
     Паскаль              1
     мм.рт.ст.            133.3223684
     кПа                  1000 Па
     psi                  6894.75729 Па
     мм.вод.ст.           9806.65
     Атмосфера техническая 98066.5 Па
     кгс/см2              98066.5 Па
     Бар                  100000 Па
     МПа                  1000000 Па
     Атмосфера физическая 101325 Па
    */
    double pressure[] = {1, 133.3223684, 1000, 6894.75729, 9806.65,
                         98066.5, 98066.5,100000, 1000000, 101325};
    double inputValue = ui->doubleSpinBoxPressureInput->value();
    double inputValueToPascals = pressure[ui->comboBoxPressureInputUnits->currentIndex()];
    inputValue *= inputValueToPascals;
    double outputValue = inputValue / pressure[ui->comboBoxPressureOutputUnits->currentIndex()];
    ui->lineEditPressureOutput->setText(QString::number(outputValue, 'f', 10));
}
void FormConverter::on_pushButtonMassConvert_clicked()
{
    /*
     Микрограмм         0.000000001 кг
     Милиграмм          0.000001 кг
     Карат              0.0002 кг
     Грамм              0.001 кг
     Унция              0.028349523125 kg
     Фунт               0.45359237 кг
     Килограмм          1 кг
     Пуд                16.3804815 кг
     Центнер            100 кг
     Тонна              1000 кг
     Килотонна          1000000 кг*/

    double mass[] = {pow(10,-9), pow(10,-6), 0.0002, pow(10,-3), 0.028349523125,
                     0.45359237, 1, 16.3804815, 100, 1000, 1000000};
    double inputValue = ui->doubleSpinBoxMassInput->value();
    double inputValueToKilogramms = mass[ui->comboBoxMassInputUnits->currentIndex()];
    inputValue *= inputValueToKilogramms;
    double outputValue = inputValue / mass[ui->comboBoxMassOutputUnits->currentIndex()];
    ui->lineEditMassOutput->setText(QString::number(outputValue, 'f', 10));
}
void FormConverter::on_pushButtonPressureClose_clicked()
{
    on_pushButtonClose_clicked();
}
void FormConverter::on_pushButtonMassClose_clicked()
{
   on_pushButtonClose_clicked();
}

void FormConverter::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key == Qt::Key_Return)
    {
        switch (ui->tabWidget->currentIndex())
        {
            case 0: on_pushButtonConvert_clicked();  break;
            case 1: on_pushButtonAreaConvert_clicked();  break;
            case 2: on_pushButtonVolumeUnitsConvert_clicked();  break;
            case 3: on_pushButtonMassConvert_clicked();    break;
            case 4: on_pushButtonPressureConvert_clicked();    break;
            case 5: on_pushButtonTemperatureConvert_clicked();   break;
            case 6: on_pushButtonSpeedConvert_clicked();     break;
            default:    break;
        }
    }
    else if(key == Qt::Key_Escape)
    {
        this->hide();
    }
    else
    {
        QWidget::keyReleaseEvent(event);
    }
}
