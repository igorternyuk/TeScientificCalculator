#include "formequations.h"
#include "ui_formequations.h"
#include "parser.h"
#ifdef DEBUG
#include <QDebug>
#endif
#include <QMessageBox>
#include <stdexcept>

FormEquations::FormEquations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormEquations)
{
    ui->setupUi(this);
    dspbx.push_back(ui->doubleSpinBoxLeftBound);
    dspbx.push_back(ui->doubleSpinBoxRightBound);
    dspbx.push_back(ui->doubleSpinBoxEpsilon);
    dspbx.push_back(ui->doubleSpinBoxLambda);
    QLocale locale(QLocale::English);
    for(auto &d : dspbx)
    {
        d->setLocale(locale);
        d->setMinimum(-99999999999.99999999);
        d->setMaximum(+99999999999.99999999);
        d->setDecimals(8);
        if(d == ui->doubleSpinBoxLambda || d == ui->doubleSpinBoxEpsilon)
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
FormEquations::~FormEquations()
{
    delete ui;
}
void FormEquations::on_pushButtonCalculate_clicked()
{
    try
    {
        const std::string input = ui->lineEditInput->text().toStdString();
        double a = ui->doubleSpinBoxLeftBound->value();
        double b = ui->doubleSpinBoxRightBound->value();
        double eps = ui->doubleSpinBoxEpsilon->value();
        int n = 0;
        double res = 0;
        if(ui->radioButtonBisectionMethod->isChecked())
        {
            std::string iterProcess;
            res = solveEquationBisectionMethod(input,'X', a, b, eps, n, iterProcess);
            ui->textEditIterProcess->clear();
            ui->textEditIterProcess->setText(QString::fromStdString(iterProcess));
        }
        else if(ui->radioButtonChordMethod->isChecked())
        {
            std::string iterProcess;
            res = solveEquationChordsMethod(input,'X', a, b, eps, n, iterProcess);
            ui->textEditIterProcess->clear();
            ui->textEditIterProcess->setText(QString::fromStdString(iterProcess));
        }
        else if(ui->radioButtonTangentMethod->isChecked())
        {
            std::string iterProcess;
            res = solveEquationTangentsMethod(input,'X', a, b, eps, n, iterProcess);
            ui->textEditIterProcess->clear();
            ui->textEditIterProcess->setText(QString::fromStdString(iterProcess));
        }
        else if(ui->radioButtonCombinedMethod->isChecked())
        {
            std::string iterProcess;
            res = solveEquationCombinedMethod(input,'X', a, b, eps, n, iterProcess);
            ui->textEditIterProcess->clear();
            ui->textEditIterProcess->setText(QString::fromStdString(iterProcess));
        }
        else
        {
            double lambda = ui->doubleSpinBoxLambda->value();
            std::string iterProcess;
            res = solveEquationIterationMethod(input,'X', a, b, eps, lambda, n, iterProcess);
            ui->textEditIterProcess->clear();
            ui->textEditIterProcess->setText(QString::fromStdString(iterProcess));
        }
        if(n >= 5000)
        {
            QMessageBox qmbx;
            qmbx.setText("Решение не найдено!");
            qmbx.exec();
            return;
        }
        int prec = ui->spinBoxPrec->value();
        ui->lineEditSolution->setText(QString::number(res, 'f', prec));
        ui->lineEditIterrationNumber->setText(QString::number(n));
    }
    catch (std::exception &e)
    {
         QMessageBox qmbx;
         qmbx.setText(e.what());
         qmbx.exec();
         return;
    }
}
void FormEquations::keyPressEvent(QKeyEvent *event)
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
