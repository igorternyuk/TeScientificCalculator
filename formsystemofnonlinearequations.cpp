#include "formsystemofnonlinearequations.h"
#include "ui_formsystemofnonlinearequations.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <stdexcept>
#include <vector>
#include <QStringList>
#include <math.h>
#include "matematica.h"
#include "parser.h"
#include "doublespinboxdelegate.h"
#ifdef DEBUG
#include <QDebug>
#endif
#include <fstream>

FormSystemOfNonLinearEquations::FormSystemOfNonLinearEquations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSystemOfNonLinearEquations)
{
    ui->setupUi(this);
    mFunctions = new QStandardItemModel(this);
    mFunctions->setColumnCount(1);
    mVarList = new QStandardItemModel(this);
    mVarList->setColumnCount(2);
    mResult = new QStandardItemModel(this);
    QStringList funcList;
    funcList.push_back("Уравнения системы");
    ui->tableViewEquations->setModel(mFunctions);
    mFunctions->setHorizontalHeaderLabels(funcList);
    ui->tableViewVarValues->setModel(mVarList);
    ui->tableViewVarValues->setItemDelegateForColumn(1, new DoubleSpinBoxDelegate(this));
    QStringList varValList;
    varValList.push_back("Переменная");
    varValList.push_back("Значение");
    mVarList->setHorizontalHeaderLabels(varValList);
    ui->tableViewResult->setModel(mResult);
    ui->spinBoxPrec->setMinimum(2);
    ui->spinBoxPrec->setMaximum(15);
    ui->spinBoxPrec->setValue(8);
    QLocale locale(QLocale::English);
    ui->doubleSpinBoxEps->setLocale(locale);
    ui->doubleSpinBoxEps->setMinimum(-99999999999.99999999);
    ui->doubleSpinBoxEps->setMaximum(+99999999999.99999999);
    ui->doubleSpinBoxEps->setDecimals(8);
    ui->doubleSpinBoxEps->setValue(0.00000000);
    ui->doubleSpinBoxEps->setSingleStep(0.001);

}

FormSystemOfNonLinearEquations::~FormSystemOfNonLinearEquations()
{
    delete ui;
}
void FormSystemOfNonLinearEquations::on_pushButtonCalculate_clicked()
{
    try
    {
        //Очищаем предыдущий результат
        mResult->clear();
        std::vector<std::string> equations1;
        //Считываем список уравнений
        for(int i = 0; i < mFunctions->rowCount(); ++i)
            equations1.push_back(getValueAt(mFunctions, i, 0).toStdString());
        //Считываем вектор пар "Имя переменной - значение"
        std::vector<std::pair<char, double>> varList;
        for(int i = 0; i < mVarList->rowCount(); ++i)
        {
            std::pair<char, double> tmp(getValueAt(mVarList, i, 0).toStdString().at(0),
                                        getValueAt(mVarList, i, 1).toDouble());
            varList.push_back(tmp);
        }
        // Считываем заданную погрешность
        double eps = ui->doubleSpinBoxEps->value();
        // Переменная для хранения количества итерраций
        int numberOfIterrations = 0;
        // Переменная для хранения результирующей погрешности
        double error = 0;
        mResult->setRowCount(equations1.size());
        mResult->setColumnCount(1);
        std::string iterProcess;
        std::vector<double> result = solveSystemOfNonLinearEquations(equations1, varList, eps,
                                                                     numberOfIterrations, error, iterProcess);
        ui->textEditIterProcess->clear();
        ui->textEditIterProcess->setText(QString::fromStdString(iterProcess));
        for(int i = 0; i < mResult->rowCount(); ++i)
        {
            if(!result.empty())
            appendTo(mResult, varList[i].first, result[i]);
        }
        int prec = ui->spinBoxPrec->value();
        ui->lineEditNumberOfIterrations->setText(QString::number(numberOfIterrations));
        ui->lineEditMeanSquareResidual->setText(QString::number(error, 'f', prec));
    }
    catch (std::exception &e)
    {
         QMessageBox qmbx;
         qmbx.setText(e.what());
         qmbx.exec();
         return;
    }
}
void FormSystemOfNonLinearEquations::keyPressEvent(QKeyEvent *event)
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
void FormSystemOfNonLinearEquations::on_pushButtonClose_clicked()
{
    close();
}
void FormSystemOfNonLinearEquations::on_spinBoxNumberOfEquations_valueChanged(int arg1)
{
    mFunctions->setRowCount(arg1);
    mVarList->setRowCount(arg1);
}
QString FormSystemOfNonLinearEquations::getValueAt(QStandardItemModel *model, int i, int j) const
{
    if(!model->item(i,j)) return QString::fromStdString(" ");
    else return model->item(i,j)->text();
}
void FormSystemOfNonLinearEquations::appendTo(QStandardItemModel *model, char var, double value) const
{
    int precision = ui->spinBoxPrec->value();
    for(int i = 0; i < model->rowCount(); ++i)
            if(!model->item(i,0))
            {
                QString tmp;
                tmp.push_back(var);
                tmp += QString::fromStdString(" = ");
                model->setItem(i, 0, new QStandardItem(tmp));
                model->setItem(i, 1, new QStandardItem(QString::number(value, 'f', precision)));
                break;
            }
}
