#include "formpartialderivatives.h"
#include "ui_formpartialderivatives.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QStringList>
#include <doublespinboxdelegate.h>
#ifdef DEBUG
#include <QDebug>
#endif
#include "parser.h"

FormPartialDerivatives::FormPartialDerivatives(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormPartialDerivatives)
{
    ui->setupUi(this);
    mArgValues = new QStandardItemModel(this);
    mPartDerivatives = new QStandardItemModel(this);
    ui->tableViewVariables->setModel(mArgValues);

    ui->tableViewVariables->setItemDelegateForColumn(1, new DoubleSpinBoxDelegate(this));
    ui->tableViewDerivatives->setModel(mPartDerivatives);
    QStringList partDerList;
    partDerList.push_back("Производная");
    partDerList.push_back("Значение");
    mPartDerivatives->setHorizontalHeaderLabels(partDerList);
    mPartDerivatives->setColumnCount(2);
    mPartDerivatives->setRowCount(2);
    QStringList argList;
    argList.push_back("Переменная");
    argList.push_back("Значение");
    mArgValues->setHorizontalHeaderLabels(argList);
    mArgValues->setColumnCount(2);
    mArgValues->setRowCount(2);
}

FormPartialDerivatives::~FormPartialDerivatives()
{
    delete ui;
}

void FormPartialDerivatives::on_pushButtonCalculate_clicked()
{
    try
    {
        mPartDerivatives->clear();
        QStringList partDerList;
        partDerList.push_back("Производная");
        partDerList.push_back("Значение");
        mPartDerivatives->setColumnCount(2);
        mPartDerivatives->setRowCount(mArgValues->rowCount());
        mPartDerivatives->setHorizontalHeaderLabels(partDerList);
        std::string input = ui->lineEditFunction->text().toStdString().c_str();
        std::vector<std::pair<char, double>> vars;
        for(int i = 0; i < mArgValues->rowCount(); ++i)
        {
            char varName = getValueAt(mArgValues, i,0).toStdString().at(0);
            double varValue = getValueAt(mArgValues, i, 1).toDouble();
            std::pair<char, double> tmp(varName, varValue);
            vars.push_back(tmp);
        }

        for(int i = 0; i < mPartDerivatives->rowCount(); ++i)
        {
            double partDer = funcPartialDer1(input, vars, getValueAt(mArgValues, i,0).toStdString().at(0));
            appendResultsTo(mArgValues, mPartDerivatives, partDer);
        }
    }
    catch (std::exception &e)
    {
        QMessageBox qmbx;
        qmbx.setText(e.what());
        qmbx.exec();
        return;
    }
}
void FormPartialDerivatives::on_pushButtonClose_clicked()
{
    close();
}
QString FormPartialDerivatives::getValueAt(QStandardItemModel *model, int i, int j) const
{
    if(!model->item(i, j)) return QString::fromStdString(" ");
    else return model->item(i, j)->text();
}
void FormPartialDerivatives::appendResultsTo(QStandardItemModel *modelArgs, QStandardItemModel *modelDers, double value) const
{
    for(int i = 0; i < modelDers->rowCount(); ++i)
    {
        if(!modelDers->item(i, 1))
        {
            int precision = ui->spinBoxPrec->value();
            modelDers->setItem(i,0, new QStandardItem("∂F/∂" + getValueAt(modelArgs, i, 0) + " = "));
            modelDers->setItem(i,1, new QStandardItem(QString::number(value, 'f', precision)));
            return;
        }
    }
}
void FormPartialDerivatives::on_spinBox_valueChanged(int arg1)
{
    mArgValues->setRowCount(arg1);
    mPartDerivatives->setRowCount(arg1);
}
void FormPartialDerivatives::keyPressEvent(QKeyEvent *event)
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
