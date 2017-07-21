#include "formintegral.h"
#include "ui_formintegral.h"
#include "parser.h"
#ifdef DEBUG
#include <QDebug>
#endif
#include <QMessageBox>
#include <stdexcept>

FormIntegral::FormIntegral(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormIntegral)
{
    ui->setupUi(this);
    qdspbx.push_back(ui->doubleSpinBoxA);
    qdspbx.push_back(ui->doubleSpinBoxB);
    qdspbx.push_back(ui->doubleSpinBoxEpsilon);
    QLocale locale(QLocale::English);
    for(auto &d : qdspbx)
    {
        d->setLocale(locale);
        d->setMinimum(-99999999999.99999999);
        d->setMaximum(+99999999999.99999999);
        d->setDecimals(8);
        if(d == ui->doubleSpinBoxEpsilon)
        {
           d->setValue(0.00100000);
           d->setSingleStep(0.001);
        }
        else
        {
            d->setValue(0.00000000);
            d->setSingleStep(0.1);
        }
    }
}
FormIntegral::~FormIntegral()
{
    delete ui;
}
void FormIntegral::on_pushButtonCalculate_clicked()
{
    try
    {
        const std::string input = ui->lineEditFunction->text().toStdString();
        double a = ui->doubleSpinBoxA->value();
        double b = ui->doubleSpinBoxB->value();
        double eps = ui->doubleSpinBoxEpsilon->value();
        int n = 0;
        double res;
        std::string iterProcess;
        if(ui->radioButtonLeftRect->isChecked())
        {
            res = integralLeftHandRect(input, 'X', a, b, eps, n, iterProcess);
        }else if(ui->radioButtonRightRect->isChecked())
        {
            res = integralRightHandRect(input, 'X', a, b, eps, n, iterProcess);
        }else if(ui->radioButtonMidleRect->isChecked())
        {
            res = integralMidpoint(input, 'X', a, b, eps, n, iterProcess);
        }else if(ui->radioButtonTrap->isChecked())
        {
           res = integralTrapezoids(input, 'X', a, b, eps, n, iterProcess);
        }else
        {
           res = integralSimpson(input, 'X', a, b, eps, n, iterProcess);
        }
        int prec = ui->spinBoxPrec->value();
        ui->lineEditRes->setText(QString::number(res, 'f', prec));
        ui->lineEditIterrationNumber->setText(QString::number(n));
        ui->textEditIterProcess->clear();
        ui->textEditIterProcess->setText(QString::fromStdString(iterProcess));
    }
    catch (std::exception &e)
    {
         QMessageBox qmbx;
         qmbx.setText(e.what());
         qmbx.exec();
         return;
    }
}
void FormIntegral::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key == Qt::Key_Return)
    {
        on_pushButtonCalculate_clicked();
    }
    if(key == Qt::Key_Escape)
    {
        close();
    }
}
