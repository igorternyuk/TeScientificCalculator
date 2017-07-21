#include "formderivative.h"
#include "ui_formderivative.h"
#include <QMessageBox>
#ifdef DEBUG
#include <QDebug>
#endif
#include "parser.h"

FormDerivative::FormDerivative(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDerivative)
{
    ui->setupUi(this);
    QLocale locale(QLocale::English);
    ui->doubleSpinBoxArgumentValue->setLocale(locale);
    ui->doubleSpinBoxArgumentValue->setMinimum(-99999999999.99999999);
    ui->doubleSpinBoxArgumentValue->setMaximum(+99999999999.99999999);
    ui->doubleSpinBoxArgumentValue->setValue(0.000000);
    ui->doubleSpinBoxArgumentValue->setDecimals(8);
    ui->doubleSpinBoxArgumentValue->setSingleStep(0.1);
    ui->spinBoxPrec->setMaximum(15);
    ui->spinBoxPrec->setMinimum(3);
    ui->spinBoxPrec->setValue(3);
}
FormDerivative::~FormDerivative()
{
    delete ui;
}

void FormDerivative::on_pushButtonCalculate_clicked()
{
    try
    {
        const std::string input = ui->lineEditFunction->text().toStdString().c_str();
        double argumentValue = ui->doubleSpinBoxArgumentValue->value();
        double leftDer1 = funcLeftDer1(input, 'X', argumentValue);
        double rightDer1 = funcRightDer1(input, 'X', argumentValue);
        double symmetricalDer1 = funcDer1(input, 'X', argumentValue);
        double der2 = funcDer2(input, 'X', argumentValue);
        double curvatura = der2 / pow(1 + pow(symmetricalDer1, 2), 1.5);
        ui->lineEditDerivativeLeft->setText(QString::number(leftDer1, 'f', ui->spinBoxPrec->value()));
        ui->lineEditDerivativeRight->setText(QString::number(rightDer1, 'f', ui->spinBoxPrec->value()));
        ui->lineEditDerivativeSymmetrical->setText(QString::number(symmetricalDer1, 'f', ui->spinBoxPrec->value()));
        ui->lineEditDerivative2->setText(QString::number(der2, 'f', ui->spinBoxPrec->value()));
        ui->lineEditCurvature->setText(QString::number(curvatura, 'f', ui->spinBoxPrec->value()));
        ui->lineEditRadiusOfCurvature->setText(QString::number(1 / curvatura, 'f', ui->spinBoxPrec->value()));
    }
    catch (std::exception &e)
    {
         QMessageBox qmbx;
         qmbx.setText(e.what());
         qmbx.exec();
         return;
    }
}
void FormDerivative::keyPressEvent(QKeyEvent *event)
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

void FormDerivative::on_pushButtonExit_clicked()
{
    close();
}
