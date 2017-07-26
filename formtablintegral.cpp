#include "formtablintegral.h"
#include "ui_formtablintegral.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QStringList>
#include "doublespinboxdelegate.h"
#include "matematica.h"

FormTablIntegral::FormTablIntegral(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTablIntegral)
{
    ui->setupUi(this);
    tabIntegrand = new QStandardItemModel(this);
    ui->tableViewIntegrand->setModel(tabIntegrand);
    ui->tableViewIntegrand->setItemDelegate(new DoubleSpinBoxDelegate(this));
    tabIntegrand->setColumnCount(2);
    QStringList list;
    list.push_back("X");
    list.push_back("Y");
    tabIntegrand->setHorizontalHeaderLabels(list);
    dspbx.push_back(ui->doubleSpinBoxA);
    dspbx.push_back(ui->doubleSpinBoxB);
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
}
FormTablIntegral::~FormTablIntegral()
{
    delete ui;
}
void FormTablIntegral::on_pushButtonCalculate_clicked()
{
    try
    {
        std::vector<std::pair<double, double>> vct;
        double a = ui->doubleSpinBoxA->value();
        double b = ui->doubleSpinBoxB->value();
        double res;
        for(int i = 0; i < tabIntegrand->rowCount(); ++i)
        {
            double X = getValueAt(tabIntegrand, i, 0);
            double Y = getValueAt(tabIntegrand, i, 1);
            std::pair<double, double> point(X, Y);
            vct.push_back(point);
        }
        if(ui->radioButtonLeftRect->isChecked())
        {
            res = iat::integralTablLeftHandRect(vct);

        }else if(ui->radioButtonRightRect->isChecked())
        {
            res = iat::integralTablRightHandRect(vct);
        }else if(ui->radioButtonTrap->isChecked())
        {
            res = iat::integralTablTrapezoids(vct);
        }else if(ui->radioButtonsimpson->isChecked())
        {
            res = iat::integralTablSimpson(vct);
        }else
        {
            res = iat::integralTablPolLagr(vct, a, b);
        }
        int prec = ui->spinBoxPrec->value();
        ui->lineEditResult->setText(QString::number(res, 'f', prec));

    }
    catch (std::exception &e)
    {
         QMessageBox qmbx;
         qmbx.setText(e.what());
         qmbx.exec();
         return;
    }
}
void FormTablIntegral::on_pushButtonClose_clicked()
{
    close();
}
void FormTablIntegral::on_spinBoxNumberOfPoints_valueChanged(int arg1)
{
    tabIntegrand->setRowCount(arg1);
}
double FormTablIntegral::getValueAt(QStandardItemModel *model, int i, int j) const
{
    if(!model->item(i, j)) return 0.0;
    else return model->item(i, j)->text().toDouble();
}
void FormTablIntegral::keyPressEvent(QKeyEvent *event)
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
