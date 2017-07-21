#ifndef FORMPARTIALDERIVATIVES_H
#define FORMPARTIALDERIVATIVES_H
#include <QWidget>
#include <QKeyEvent>
#include <Qt>

namespace Ui
{
    class FormPartialDerivatives;
}
class QStandardItemModel;

class FormPartialDerivatives : public QWidget
{
    Q_OBJECT

public:
    explicit FormPartialDerivatives(QWidget *parent = 0);
    ~FormPartialDerivatives();

private slots:
    void on_pushButtonCalculate_clicked();
    void on_pushButtonClose_clicked();
    void on_spinBox_valueChanged(int arg1);

protected:
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::FormPartialDerivatives *ui;
    QStandardItemModel *mArgValues;
    QStandardItemModel *mPartDerivatives;
    void appendResultsTo(QStandardItemModel *modelArgs, QStandardItemModel *modelDers, double value) const;
    QString getValueAt(QStandardItemModel *model, int i, int j) const;
};

#endif // FORMPARTIALDERIVATIVES_H
