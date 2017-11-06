#ifndef FORMTABLDIFF_H
#define FORMTABLDIFF_H

#include <QWidget>
#include <QKeyEvent>
#include <Qt>

namespace Ui
{
    class FormTablDiff;
}

class QStandardItemModel;
class FormTablDiff : public QWidget
{
    Q_OBJECT

public:
    explicit FormTablDiff(QWidget *parent = nullptr);
    ~FormTablDiff();

protected:
    void keyReleaseEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent*) override;

private slots:
    void on_spinBoxNumberOfPoints_valueChanged(int arg1);
    void on_pushButtonCalculate_clicked();
    void on_pushButtonClose_clicked();
    double getTableItemValue(QStandardItemModel *model, int i, int j) const;

private:
    Ui::FormTablDiff *ui;
    QStandardItemModel *mPointsTable;
};

#endif // FORMTABLDIFF_H
