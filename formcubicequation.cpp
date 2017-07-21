#include "formcubicequation.h"
#include "ui_formcubicequation.h"
#include "matematica.h"
#include <complex>
#include <vector>
#include <math.h>
#include <stdexcept>
#include <QMessageBox>

FormCubicEquation::FormCubicEquation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCubicEquation)
{
    ui->setupUi(this);
    dspbx.push_back(ui->doubleSpinBoxA);
    dspbx.push_back(ui->doubleSpinBoxB);
    dspbx.push_back(ui->doubleSpinBoxC);
    dspbx.push_back(ui->doubleSpinBoxD);
    for(auto &d : dspbx)
    {
        QLocale locale(QLocale::English);
        d->setLocale(locale);
        d->setMinimum(-99999999999.99999999);
        d->setMaximum(+99999999999.99999999);
        d->setValue(0.00000000);
        d->setDecimals(8);
        d->setSingleStep(0.1);
    }
    ui->spinBoxPrec->setMinimum(2);
    ui->spinBoxPrec->setMaximum(15);
    ui->spinBoxPrec->setValue(8);
}

FormCubicEquation::~FormCubicEquation()
{
    delete ui;

}
void FormCubicEquation::on_pushButtonCalculate_clicked()
{
    try
    {
        double a = ui->doubleSpinBoxA->value();
        double b = ui->doubleSpinBoxB->value();
        double c = ui->doubleSpinBoxC->value();
        double d = ui->doubleSpinBoxD->value();
        std::vector<std::complex<double>> roots;
        roots = solveCubicEquation(a, b, c, d);
        int prec = ui->spinBoxPrec->value();
        if(!roots.empty())
        {
            if(roots[0].imag() > 0.0)
               ui->labelX1->setText("X1 = " + QString::number(roots[0].real(), 'f', prec) + " + " + QString::number(fabs(roots[0].imag()), 'f', prec) + "j");
            else if(roots[0].imag() < 0.0)
               ui->labelX1->setText("X1 = " + QString::number(roots[0].real(), 'f', prec) + " - " + QString::number(fabs(roots[0].imag()), 'f', prec) + "j");
            else
                ui->labelX1->setText("X1 = " + QString::number(roots[0].real(), 'f', prec));
            if(roots[1].imag() > 0.0)
                ui->labelX2->setText("X2 = " + QString::number(roots[1].real(), 'f', prec) + " + " + QString::number(fabs(roots[1].imag()), 'f', prec) + "j");
            else if(roots[1].imag() < 0.0)
                ui->labelX2->setText("X2 = " + QString::number(roots[1].real(), 'f', prec) + " - " + QString::number(fabs(roots[1].imag()), 'f', prec) + "j");
            else
                ui->labelX2->setText("X2 = " + QString::number(roots[1].real(), 'f', prec));
            if(roots[2].imag() > 0.0)
                ui->labelX3->setText("X3 = " + QString::number(roots[2].real(), 'f', prec) + " + " + QString::number(fabs(roots[2].imag()), 'f', prec) + "j");
            else if(roots[2].imag() < 0.0)
                ui->labelX3->setText("X3 = " + QString::number(roots[2].real(), 'f', prec) + " - " + QString::number(fabs(roots[2].imag()), 'f', prec) + "j");
            else
                ui->labelX3->setText("X3 = " + QString::number(roots[2].real(), 'f', prec));
        }
    }
    catch (std::exception &e)
    {
        QMessageBox q;
        q.setText(e.what());
        q.exec();
    }
}
void FormCubicEquation::keyPressEvent(QKeyEvent *event)
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
