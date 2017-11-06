#ifndef FORMTABLINTEGRAL_H
#define FORMTABLINTEGRAL_H

#include <QWidget>
#include <QKeyEvent>
#include <Qt>
#include <QDoubleSpinBox>

namespace Ui
{
    class FormTablIntegral;
}

class QStandardItemModel;
class FormTablIntegral : public QWidget
{
    Q_OBJECT

public:
    explicit FormTablIntegral(QWidget *parent = nullptr);
    ~FormTablIntegral();

protected:
    void keyReleaseEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent*) override;

private slots:
    void on_pushButtonCalculate_clicked();
    void on_pushButtonClose_clicked();
    void on_spinBoxNumberOfPoints_valueChanged(int arg1);
    double getValueAt(QStandardItemModel *model, int i, int j) const;

private:
    Ui::FormTablIntegral *ui;
    QStandardItemModel *tabIntegrand;
    std::vector<QDoubleSpinBox*> dspbx;
};

#endif // FORMTABLINTEGRAL_H
