#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qt>
#include <QKeyEvent>
#include <QDoubleSpinBox>
#include <QStandardItemModel>

class QStandardItemModel;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton0_clicked();
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    void on_pushButton3_clicked();
    void on_pushButton4_clicked();
    void on_pushButton5_clicked();
    void on_pushButton6_clicked();
    void on_pushButton7_clicked();
    void on_pushButton8_clicked();
    void on_pushButton9_clicked();
    void on_pushButtonDot_clicked();
    void on_pushButtonEquals_clicked();
    void on_pushButtonPlus_clicked();
    void on_pushButtonMinus_clicked();
    void on_pushButtonMultiplicate_clicked();
    void on_pushButtoDivide_clicked();
    void on_pushButtonSinus_clicked();
    void on_pushButtonCosinus_clicked();
    void on_pushButtonTangent_clicked();
    void on_pushButtonCotangent_clicked();
    void on_pushButtonSecans_clicked();
    void on_pushButtonCosecans_clicked();
    void on_pushButtonArcSinus_clicked();
    void on_pushButtonArcCosinus_clicked();
    void on_pushButtonArcTangent_clicked();
    void on_pushButtonArcCotangent_clicked();
    void on_pushButtonArcSecans_clicked();
    void on_pushButtonArcCosecans_clicked();
    void on_pushButtonLess_clicked();
    void on_pushButtonLessOrEquals_clicked();
    void on_pushButtonMore_clicked();
    void on_pushButtonMoreOrEquals_clicked();
    void on_pushButtonAnd_clicked();
    void on_pushButtonOr_clicked();
    void on_pushButtonXor_clicked();
    void on_pushButtonNot_clicked();
    void on_pushButtonCalculate_clicked();
    void on_pushButtonNotEquals_clicked();
    void on_pushButtonLn_clicked();
    void on_pushButtonLog2_clicked();
    void on_pushButtoLog8_clicked();
    void on_pushButtonLog10_clicked();
    void on_pushButtonLog16_clicked();
    void on_pushButtonPI_clicked();
    void on_pushButtonExp_clicked();
    void on_pushButtonSquareRoot_clicked();
    void on_pushButtonCubicRoot_clicked();
    void on_pushButtonSquare_clicked();
    void on_pushButtonCube_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonClearAll_clicked();
    void on_pushButtonLeftParentethis_clicked();
    void on_pushButtonRightParentethis_clicked();
    void on_pushButtonMod_clicked();
    void on_pushButtonAbs_clicked();
    void on_pushButtonAns_clicked();
    void on_pushButtonPower_clicked();
    void on_pushButtonE_clicked();
    void on_pushButtonExit_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonFactorial_clicked();
    void on_pushButtonMemPlus_clicked();
    void on_pushButtonMeminus_clicked();
    void on_pushButtonMemMultiplicate_clicked();
    void on_pushButtonMemDivide_clicked();
    void on_pushButtonLMemRes_clicked();
    void on_MemClear_clicked();
    void insertOperatorName(std::string s);
    void on_spinBoxVariables_valueChanged(int arg1);
    void on_saveResults_triggered();
    void on_squareEquation_triggered();
    void on_cubicEquation_triggered();
    void on_solveEquation_triggered();
    void on_actionConverter_triggered();
    void on_analiticIntegral_triggered();
    void on_tablIntegral_triggered();
    void on_derivativeFx_triggered();
    void on_partialDerivativesFxyz_triggered();
    void on_diffTablfunc_triggered();
    void on_systNonLinearEquations_triggered();
    QString getValueAt(QStandardItemModel *model, int i, int j) const;
    void appendTo(QStandardItemModel *model, double value) const;
    void appendTo(QStandardItemModel *model, QString item) const;
    void clearCalculationsHistory();
    void openFile();
    void saveFile();
    void on_loadCalcHistory_triggered();
    void on_clearCalcHistory_triggered();
    void on_pushButtonInverseValue_clicked();
    void on_action_triggered();
    void on_tableViewResults_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *resTable;
    QStandardItemModel *varTable;
    double valueInMemory;

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
