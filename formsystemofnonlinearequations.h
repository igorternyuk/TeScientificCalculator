#ifndef FORMSYSTEMOFNONLINEAREQUATIONS_H
#define FORMSYSTEMOFNONLINEAREQUATIONS_H

#include <QWidget>
#include <QKeyEvent>
#include <Qt>
namespace Ui
{
class FormSystemOfNonLinearEquations;
}
class QStandardItemModel;
class FormSystemOfNonLinearEquations : public QWidget
{
    Q_OBJECT

public:
    explicit FormSystemOfNonLinearEquations(QWidget *parent = 0);
    ~FormSystemOfNonLinearEquations();

private slots:
    void on_pushButtonCalculate_clicked();
    void on_pushButtonClose_clicked();
    void on_spinBoxNumberOfEquations_valueChanged(int arg1);
    QString getValueAt(QStandardItemModel *model, int i, int j) const;
    void appendTo(QStandardItemModel *model, char var, double value) const;

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::FormSystemOfNonLinearEquations *ui;
    QStandardItemModel *mFunctions;
    QStandardItemModel *mVarList;
    QStandardItemModel *mResult;
};

#endif // FORMSYSTEMOFNONLINEAREQUATIONS_H
