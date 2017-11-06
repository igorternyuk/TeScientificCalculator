#include "formsquareequation.h"
#include "ui_formsquareequation.h"

#include "matematica.h"

#include <vector>
#include <complex>
#include <QCloseEvent>

FormSquareEquation::FormSquareEquation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSquareEquation)
{
    ui->setupUi(this);
    dspbx.push_back(ui->doubleSpinBoxA);
    dspbx.push_back(ui->doubleSpinBoxB);
    dspbx.push_back(ui->doubleSpinBoxC);
    for(auto &d : dspbx)
    {
        QLocale locale(QLocale::English);
        d->setLocale(locale);
        d->setMinimum(-99999999999.99999999);
        d->setMaximum(+99999999999.99999999);
        d->setDecimals(8);
        d->setValue(0.00000000);
        d->setSingleStep(0.1);
        ui->spinBoxPrec->setMinimum(2);
        ui->spinBoxPrec->setMaximum(15);
        ui->spinBoxPrec->setValue(8);
    }
}

FormSquareEquation::~FormSquareEquation()
{
    delete ui;
}

void FormSquareEquation::on_pushButtonCalculate_clicked()
{
    double a = ui->doubleSpinBoxA->value();
    double b = ui->doubleSpinBoxB->value();
    double c = ui->doubleSpinBoxC->value();
    int prec = ui->spinBoxPrec->value();
    std::vector<std::complex<double>> roots = iat::solveSquareEquation(a, b, c);
    if(!roots.empty())
    {
        if(roots[0].imag() != 0)
             ui->labelX1->setText("X1 = " + QString::number(roots[0].real(), 'f', prec) +
                                 "+" + QString::number(fabs(roots[0].imag()), 'f', prec) + "j");
        else ui->labelX1->setText("X1 = " + QString::number(roots[0].real(), 'f', prec));
        if(roots[1].imag() != 0)
             ui->labelX2->setText("X2 = " + QString::number(roots[1].real(), 'f', prec) +
             QString::number(roots[1].imag(), 'f', prec) + "j");
        else
             ui->labelX2->setText("X2 = " + QString::number(roots[1].real(), 'f', prec));
    }
}

void FormSquareEquation::on_pushButtonClose_clicked()
{
    this->hide();
}

void FormSquareEquation::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key == Qt::Key_Return)
    {
        on_pushButtonCalculate_clicked();
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

void FormSquareEquation::closeEvent(QCloseEvent *)
{
    this->hide();
}
