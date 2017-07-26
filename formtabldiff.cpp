#include "formtabldiff.h"
#include "ui_formtabldiff.h"
#include <QStandardItemModel>
#include <QStringList>
#include <QMessageBox>
#include <vector>
#include <stdexcept>
#include "doublespinboxdelegate.h"
#include "matematica.h"

using namespace iat;

FormTablDiff::FormTablDiff(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTablDiff)
{
    ui->setupUi(this);
    mPointsTable = new QStandardItemModel(this);
    ui->tableView->setModel(mPointsTable);
    ui->tableView->setItemDelegate(new DoubleSpinBoxDelegate(this));
    mPointsTable->setColumnCount(2);
    QStringList argsList;
    argsList.push_back("X");
    argsList.push_back("Y");
    mPointsTable->setHorizontalHeaderLabels(argsList);
    QLocale locale(QLocale::English);
    ui->doubleSpinBoxArgValue->setLocale(locale);
    ui->doubleSpinBoxArgValue->setMinimum(-99999999999.99999999);
    ui->doubleSpinBoxArgValue->setMaximum(+99999999999.99999999);
    ui->doubleSpinBoxArgValue->setDecimals(8);
    ui->doubleSpinBoxArgValue->setValue(0.00000000);
    ui->doubleSpinBoxArgValue->setSingleStep(0.1);
    ui->spinBoxPrec->setMaximum(15);
    ui->spinBoxPrec->setMinimum(2);
    ui->spinBoxPrec->setValue(8);
}
FormTablDiff::~FormTablDiff()
{
    delete ui;
}
void FormTablDiff::on_spinBoxNumberOfPoints_valueChanged(int arg1)
{
    mPointsTable->setRowCount(arg1);
}
void FormTablDiff::on_pushButtonCalculate_clicked()
{
    try
    {
        std::vector<std::pair<double, double>> points;
        for(int i = 0; i < mPointsTable->rowCount(); ++i)
        {
            std::pair<double, double> point(getTableItemValue(mPointsTable, i, 0),
                                            getTableItemValue(mPointsTable, i, 1));
            points.push_back(point);
    }
        double value = ui->doubleSpinBoxArgValue->value();
        int prec = ui->spinBoxPrec->value();
        double firstDer = tablFuncDer1(points, value);
        double secondDer = tablFuncDer2(points, value);
        double curvatura = secondDer / pow(1 + pow(firstDer, 2), 1.5);
        double curvRad = fabs(1 / curvatura);
        ui->lineEditFunc->setText(QString::number(polynomLagrange(points, value), 'f', prec));
        ui->lineEditLeftDer1->setText(QString::number(tablFuncLeftDer1(points, value), 'f', prec));
        ui->lineEditRightDer1->setText(QString::number(tablFuncRightDer1(points, value), 'f', prec));
        ui->lineEditDer1->setText(QString::number(firstDer, 'f', prec));
        ui->lineEditDer2->setText(QString::number(secondDer, 'f', prec));
        ui->lineEditCurvature->setText(QString::number(curvatura, 'f', prec));
        ui->lineEditRadiusOfCurvature->setText(QString::number(curvRad, 'f', prec));
    }
    catch (std::exception & e)
    {
        QMessageBox q;
        q.setText(e.what());
        q.exec();
    }
}
void FormTablDiff::on_pushButtonClose_clicked()
{
    close();
}
double FormTablDiff::getTableItemValue(QStandardItemModel *model, int i, int j) const
{
    if(!model->item(i, j)) return 0.0;
    else return model->item(i, j)->text().toDouble();
}
void FormTablDiff::keyPressEvent(QKeyEvent *event)
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
