#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QDoubleSpinBox>
#ifdef DEBUG
#include <QDebug>
#endif
#include "parser.h"
#include "matematica.h"
#include "formequations.h"
#include "formderivative.h"
#include "formintegral.h"
#include "formconverter.h"
#include "doublespinboxdelegate.h"
#include "formsquareequation.h"
#include "formcubicequation.h"
#include "formtablintegral.h"
#include "formpartialderivatives.h"
#include "formtabldiff.h"
#include "formsystemofnonlinearequations.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resTable = new QStandardItemModel(this);
    resTable->setColumnCount(2);
    ui->tableViewResults->setModel(resTable);
    varTable = new QStandardItemModel(this);
    ui->tableViewVariables->setModel(varTable);
    ui->tableViewVariables->setItemDelegateForColumn(1, new DoubleSpinBoxDelegate(this));
    varTable->setColumnCount(2);
    ui->spinBox->setValue(6);
    ui->spinBox->setMaximum(16);
    ui->spinBox->setMinimum(1);
    valueInMemory = 0.0;
    ui->lineEditInput->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButtonCalculate_clicked()
{
    try
    {        
        std::string input = ui->lineEditInput->text().toStdString().c_str();
        std::vector<std::pair<char, double>> vctVars;
        for(int i = 0; i < varTable->rowCount(); ++i)
        {
            std::pair<char, double> pTmp(getValueAt(varTable, i, 0).toStdString().at(0), getValueAt(varTable, i, 1).toDouble());
            vctVars.push_back(pTmp);
        }
        std::string angleUnit;
        switch (ui->comboBoxGradusRadians->currentIndex()) {
            case 2: angleUnit = "grad"; break;
            case 1: angleUnit = "gradus"; break;
            case 0:
            default:angleUnit = "radian"; break;
        }
        Parser prs(input, vctVars, angleUnit);
        auto resultOfParsing = prs.calculateExpression();
        //Если парсер кинул исключение то строку в таблицу результатов не добавляем
        resTable->setRowCount(resTable->rowCount()+1);
        appendTo(resTable, resultOfParsing);
    }
    catch (std::exception &e)
    {
         QMessageBox qmbx;
         qmbx.critical(this, "Error", QString::fromStdString(e.what()));
         //qmbx.setText(e.what());
         //qmbx.exec();
         return;
    }
}
void MainWindow::keyPressEvent(QKeyEvent *event)
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
//*******************Actions**********************
//Уравнения
void MainWindow::on_saveResults_triggered()
{
    saveFile();
}
void MainWindow::on_loadCalcHistory_triggered()
{
    openFile();
}
void MainWindow::on_clearCalcHistory_triggered()
{
    clearCalculationsHistory();
}
void MainWindow::on_squareEquation_triggered()
{
    FormSquareEquation *frmSqEq = new FormSquareEquation();
    QRect myScreenGeometry = QApplication::desktop()->geometry() ;
    int x = (myScreenGeometry.width() - frmSqEq->width()) / 2;
    int y = (myScreenGeometry.height() - frmSqEq->height()) / 2;
    frmSqEq->move(x, y);
    frmSqEq->show();
}
void MainWindow::on_cubicEquation_triggered()
{
    FormCubicEquation *frmCbEq = new FormCubicEquation();
    QRect myScreenGeometry = QApplication::desktop()->geometry() ;
    int x = (myScreenGeometry.width() - frmCbEq->width()) / 2;
    int y = (myScreenGeometry.height() - frmCbEq->height()) / 2;
    frmCbEq->move(x, y);
    frmCbEq->show();
}
void MainWindow::on_solveEquation_triggered()
{
    FormEquations *frmEq = new FormEquations();
    QRect myScreenGeometry = QApplication::desktop()->geometry() ;
    int x = (myScreenGeometry.width() - frmEq->width()) / 2;
    int y = (myScreenGeometry.height() - frmEq->height()) / 2;
    frmEq->move(x, y);
    frmEq->show();
}
void MainWindow::on_actionConverter_triggered()
{
    FormConverter *frmConv = new FormConverter();
    QRect myScreenGeometry = QApplication::desktop()->geometry() ;
    int x = (myScreenGeometry.width() - frmConv->width()) / 2;
    int y = (myScreenGeometry.height() - frmConv->height()) / 2;
    frmConv->move(x, y);
    frmConv->show();
}
void MainWindow::on_analiticIntegral_triggered()
{
    FormIntegral *frmIntegral = new FormIntegral();
    QRect myScreenGeometry = QApplication::desktop()->geometry() ;
    int x = (myScreenGeometry.width() - frmIntegral->width()) / 2;
    int y = (myScreenGeometry.height() - frmIntegral->height()) / 2;
    frmIntegral->move(x, y);
    frmIntegral->show();
}
void MainWindow::on_tablIntegral_triggered()
{
    FormTablIntegral *frmTabIntegral = new FormTablIntegral();
    QRect myScreenGeometry = QApplication::desktop()->geometry() ;
    int x = (myScreenGeometry.width() - frmTabIntegral->width()) / 2;
    int y = (myScreenGeometry.height() - frmTabIntegral->height()) / 2;
    frmTabIntegral->move(x, y);
    frmTabIntegral->show();
}
void MainWindow::on_derivativeFx_triggered()
{
    FormDerivative *frmDer = new FormDerivative();
    QRect myScreenGeometry = QApplication::desktop()->geometry() ;
    int x = (myScreenGeometry.width() - frmDer->width()) / 2;
    int y = (myScreenGeometry.height() - frmDer->height()) / 2;
    frmDer->move(x, y);
    frmDer->show();
}
void MainWindow::on_partialDerivativesFxyz_triggered()
{
    FormPartialDerivatives *frmPrtDer = new FormPartialDerivatives();
    QRect myScreenGeometry = QApplication::desktop()->geometry() ;
    int x = (myScreenGeometry.width() - frmPrtDer->width()) / 2;
    int y = (myScreenGeometry.height() - frmPrtDer->height()) / 2;
    frmPrtDer->move(x, y);
    frmPrtDer->show();
}
void MainWindow::on_diffTablfunc_triggered()
{
    FormTablDiff *frmTblDiff = new FormTablDiff();
    QRect myScreenGeometry = QApplication::desktop()->geometry() ;
    int x = (myScreenGeometry.width() - frmTblDiff->width()) / 2;
    int y = (myScreenGeometry.height() - frmTblDiff->height()) / 2;
    frmTblDiff->move(x, y);
    frmTblDiff->show();
}
void MainWindow::on_systNonLinearEquations_triggered()
{
    FormSystemOfNonLinearEquations *frmSyst = new FormSystemOfNonLinearEquations();
    QRect myScreenGeometry = QApplication::desktop()->geometry() ;
    int x = (myScreenGeometry.width() -frmSyst->width()) / 2;
    int y = (myScreenGeometry.height() - frmSyst->height()) / 2;
    frmSyst->move(x, y);
    frmSyst->show();
}
void MainWindow::openFile()
{
    /*QFileDialog::getOpenFileName(this, QString::fromStdString("Загрузить расчеты из файла"),
                 QDir::currentPath(), QString::fromStdString("Текстовые файлы (*txt *.dat);;Все файлы (*.*)"),
                 0, QFileDialog::DontUseNativeDialog);*/
    QString fileName = QFileDialog::getOpenFileName(
                this,
                QString::fromStdString("Открыть файл"),
                QDir::currentPath(),
                QString::fromStdString("Текстовые документы (*.txt *.dat);;Все файлы (*.*)"));
    if(!fileName.isEmpty())
    {
        std::ifstream fi(fileName.toStdString());
        int row, col;
        fi >> row >> col;
        resTable->setRowCount(row);
        resTable->setColumnCount(col);
        for(int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
              std::string item;
              fi >> item;
              appendTo(resTable,QString::fromStdString(item));
            }
        }
        fi.close();
    }
}
void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(
                this,
                QString::fromStdString("Сохранить результаты расчетов в текстовый файл ..."),
                QDir::currentPath(),
                QString::fromStdString("Текстовые документы (*.txt)"));
    std::ofstream fo(fileName.toStdString());
    fo << resTable->rowCount() << " " << resTable->columnCount() << "\n";
    for(int i = 0; i < resTable->rowCount(); ++i)
    {
        fo << getValueAt(resTable, i,0).toStdString() <<
              getValueAt(resTable, i,1).toStdString() << std::endl;
    }
    fo.close();
}

//*******************Models**********************
void MainWindow::on_spinBoxVariables_valueChanged(int arg1)
{
    varTable->setRowCount(arg1);
}
QString MainWindow::getValueAt(QStandardItemModel *model, int i, int j) const
{
    if(!model->item(i, j)) return QString::fromStdString(" ");
    else return model->item(i, j)->text();
}
void MainWindow::appendTo(QStandardItemModel *model, double value) const
{
    for(int i = 0; i < model->rowCount(); ++i)
    {
        if(!model->item(i,0))
        {
            int precision = ui->spinBox->value();
            model->setItem(i,0, new QStandardItem(ui->lineEditInput->text() + "= "));
            model->item(i,0)->setEditable(false);
            model->setItem(i,1, new QStandardItem(QString::number(value, 'f', precision )));
            model->item(i,1)->setEditable(false);
            return;
        }
    }
}
void MainWindow::appendTo(QStandardItemModel *model, QString item) const
{
    for(int i = 0; i < model->rowCount(); ++i)
    {
        for(int j = 0; j < model->columnCount(); ++j)
        {
            if(!model->item(i, j))
            {
                model->setItem(i,j, new QStandardItem(item));
                model->item(i, j)->setEditable(false);
                return;
            }
        }
    }
}
void MainWindow::clearCalculationsHistory()
{
   resTable->clear();
   resTable->setColumnCount(2);
}
void MainWindow::insertOperatorName(std::string s)
{
    //ui->lineEditInput->setFocus();
    //Определяем текущую позицию курсора
    int currentPos = ui->lineEditInput->cursorPosition();
    //Сохраняем текущий текст поля ввода в буферную строковую переменную
    std::string str_buf = ui->lineEditInput->text().toStdString();
    //Копируем часть этой строки с начала до текущей позиции курсора
    std::string buf1 = str_buf.substr(0,currentPos);
    //Копируем часть этой строки с текущей позиции курсора до конца
    std::string buf2 = str_buf.substr(currentPos, str_buf.length() - currentPos);
    //Добавляем к первой части переданную строку оператора
    buf1 += s;
    //Конкатинируем строки
    str_buf = buf1 + buf2;
    //Устанавливаем новый текст в поле ввода
    ui->lineEditInput->setText(QString::fromStdString(str_buf));
    //Передвигаем курсор на длину строки оператора
    ui->lineEditInput->setCursorPosition(currentPos + s.length() - 1);
    //Устанавливаем фокус на поле ввода
    ui->lineEditInput->setFocus();    
}
// Метод который сохраняет в файл результаты расчетов
void MainWindow::on_pushButtonSave_clicked()
{
      saveFile();
}
void MainWindow::on_pushButtonEquals_clicked()
{
   insertOperatorName("==");
   ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButton0_clicked()
{
    insertOperatorName("0");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButton1_clicked()
{
    insertOperatorName("1");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButton2_clicked()
{
    insertOperatorName("2");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButton3_clicked()
{
    insertOperatorName("3");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButton4_clicked()
{
    insertOperatorName("4");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButton5_clicked()
{
    insertOperatorName("5");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButton6_clicked()
{
    insertOperatorName("6");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButton7_clicked()
{
    insertOperatorName("7");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButton8_clicked()
{
    insertOperatorName("8");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButton9_clicked()
{
    insertOperatorName("9");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonDot_clicked()
{
    insertOperatorName(".");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonPlus_clicked()
{
    insertOperatorName("+");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonMinus_clicked()
{
    insertOperatorName("-");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonMultiplicate_clicked()
{
    insertOperatorName("*");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtoDivide_clicked()
{
    insertOperatorName("/");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonSinus_clicked()
{
    if(ui->comboBoxTrHyp->currentIndex() == 0)
        insertOperatorName("sin()");
    else
        insertOperatorName("sh()");
}
void MainWindow::on_pushButtonCosinus_clicked()
{
    if(ui->comboBoxTrHyp->currentIndex() == 0)
        insertOperatorName("cos()");
    else
        insertOperatorName("ch()");
}
void MainWindow::on_pushButtonTangent_clicked()
{
    if(ui->comboBoxTrHyp->currentIndex() == 0)
        insertOperatorName("tg()");
    else
        insertOperatorName("th()");
}
void MainWindow::on_pushButtonCotangent_clicked()
{
    if(ui->comboBoxTrHyp->currentIndex() == 0)
        insertOperatorName("ctg()");
    else
        insertOperatorName("cth()");
}
void MainWindow::on_pushButtonSecans_clicked()
{
    if(ui->comboBoxTrHyp->currentIndex() == 0)
        insertOperatorName("secans()");
    else
        insertOperatorName("sech()");
}
void MainWindow::on_pushButtonCosecans_clicked()
{
    if(ui->comboBoxTrHyp->currentIndex() == 0)
        insertOperatorName("ccecans()");
    else
        insertOperatorName("csech()");
}
void MainWindow::on_pushButtonArcSinus_clicked()
{
    if(ui->comboBoxTrHyp->currentIndex() == 0)
        insertOperatorName("arcsin()");
    else
        insertOperatorName("arcsh()");
}
void MainWindow::on_pushButtonArcCosinus_clicked()
{
    if(ui->comboBoxTrHyp->currentIndex() == 0)
        insertOperatorName("arccos()");
    else
        insertOperatorName("arcch()");
}
void MainWindow::on_pushButtonArcTangent_clicked()
{
    if(ui->comboBoxTrHyp->currentIndex() == 0)
        insertOperatorName("arctg()");
    else
        insertOperatorName("arcth()");
}
void MainWindow::on_pushButtonArcCotangent_clicked()
{
    if(ui->comboBoxTrHyp->currentIndex() == 0)
        insertOperatorName("arcctg()");
    else
        insertOperatorName("arccth()");
}
void MainWindow::on_pushButtonArcSecans_clicked()
{
    if(ui->comboBoxTrHyp->currentIndex() == 0)
        insertOperatorName("arcsecans()");
    else
        insertOperatorName("arcsech()");
}
void MainWindow::on_pushButtonArcCosecans_clicked()
{
    if(ui->comboBoxTrHyp->currentIndex() == 0)
        insertOperatorName("arccsecans()");
    else
        insertOperatorName("arccsech()");
}
void MainWindow::on_pushButtonLess_clicked()
{
    insertOperatorName("<");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonLessOrEquals_clicked()
{
    insertOperatorName("<=");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonMore_clicked()
{
    insertOperatorName(">");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonMoreOrEquals_clicked()
{
    insertOperatorName(">=");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonAnd_clicked()
{
    insertOperatorName("&");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonOr_clicked()
{
    insertOperatorName("|");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonXor_clicked()
{
    insertOperatorName("^");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonNot_clicked()
{
   insertOperatorName("!()");
}
void MainWindow::on_pushButtonNotEquals_clicked()
{
    insertOperatorName("!=");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonLn_clicked()
{
    insertOperatorName("ln()");
}
void MainWindow::on_pushButtonLog2_clicked()
{
    insertOperatorName("log2()");
}
void MainWindow::on_pushButtoLog8_clicked()
{
    insertOperatorName("log8()");
}
void MainWindow::on_pushButtonLog10_clicked()
{
    insertOperatorName("log10()");
}
void MainWindow::on_pushButtonLog16_clicked()
{
    insertOperatorName("log16()");
}
void MainWindow::on_pushButtonPI_clicked()
{
    insertOperatorName("P");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonExp_clicked()
{
    insertOperatorName("_exp()");
}
void MainWindow::on_pushButtonSquareRoot_clicked()
{
    insertOperatorName("sqrt()");
}
void MainWindow::on_pushButtonCubicRoot_clicked()
{
   insertOperatorName("cbrt()");
}
void MainWindow::on_pushButtonSquare_clicked()
{
   insertOperatorName("sqr()");
}
void MainWindow::on_pushButtonCube_clicked()
{
   insertOperatorName("cube()");
}
void MainWindow::on_pushButtonInverseValue_clicked()
{
   insertOperatorName("inv()");
}
void MainWindow::on_pushButtonClear_clicked()
{
    if(ui->lineEditInput->text() != "")
    {
        int currentPos = ui->lineEditInput->cursorPosition();
        if (currentPos == 0) return;
        //Сохраняем текущий текст поля ввода в буферную строковую переменную
        std::string str_buf = ui->lineEditInput->text().toStdString();
        //Копируем часть этой строки с начала до текущей позиции курсора
        std::string buf1 = str_buf.substr(0,currentPos);
        //Копируем часть этой строки с текущей позиции курсора до конца
        std::string buf2 = str_buf.substr(currentPos, str_buf.length() - currentPos);
        //Добавляем к первой части переданную строку оператора
        buf1.pop_back();
        //Конкатинируем строки
        str_buf = buf1 + buf2;
        //Устанавливаем новый текст в поле ввода
        ui->lineEditInput->setText(QString::fromStdString(str_buf));
        //Передвигаем курсор на длину строки оператора
        ui->lineEditInput->setCursorPosition(currentPos - 1);
        //Устанавливаем фокус на поле ввода
        ui->lineEditInput->setFocus();
    }
}
void MainWindow::on_pushButtonClearAll_clicked()
{
  if(ui->lineEditInput->text() != "")
      ui->lineEditInput->setText("");
}
void MainWindow::on_pushButtonLeftParentethis_clicked()
{
    insertOperatorName("(");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonRightParentethis_clicked()
{
    insertOperatorName(")");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonMod_clicked()
{
    insertOperatorName("mod");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonAbs_clicked()
{
    insertOperatorName("abs()");
}
void MainWindow::on_pushButtonAns_clicked()
{
    if(resTable->rowCount() > 0)
    {
        QString tmp = getValueAt(resTable, resTable->rowCount() - 1, 1);
        insertOperatorName(tmp.toStdString());
        ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
    }
}
void MainWindow::on_pushButtonPower_clicked()
{
    insertOperatorName("**");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonE_clicked()
{
    insertOperatorName("E");
    ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
}
void MainWindow::on_pushButtonFactorial_clicked()
{
    insertOperatorName("factorial()");
}
void MainWindow::on_pushButtonExit_clicked()
{
    close();
}
void MainWindow::on_pushButtonMemPlus_clicked()
{
    if(resTable->rowCount() > 0)
          valueInMemory += getValueAt(resTable, resTable->rowCount() - 1, 1).toDouble();
}
void MainWindow::on_pushButtonMeminus_clicked()
{
    if(resTable->rowCount() > 0)
          valueInMemory -= getValueAt(resTable, resTable->rowCount() - 1, 1).toDouble();
}
void MainWindow::on_pushButtonMemMultiplicate_clicked()
{
    if(resTable->rowCount() > 0)
          valueInMemory *= getValueAt(resTable, resTable->rowCount() - 1, 1).toDouble();
}
void MainWindow::on_pushButtonMemDivide_clicked()
{
    if(resTable->rowCount() > 0 && getValueAt(resTable, resTable->rowCount() - 1, 1).toDouble() != 0)
          valueInMemory /= getValueAt(resTable, resTable->rowCount() - 1, 1).toDouble();
}
void MainWindow::on_pushButtonLMemRes_clicked()
{
    if(resTable->rowCount() > 0)
    {
          QString memVal = QString::number(valueInMemory, 'f', ui->spinBox->value());
          insertOperatorName(memVal.toStdString());
          ui->lineEditInput->setCursorPosition(ui->lineEditInput->cursorPosition() + 1);
    }
}
void MainWindow::on_MemClear_clicked()
{
    valueInMemory = 0.0;
}

void MainWindow::on_action_triggered()
{
    close();
}

void MainWindow::on_tableViewResults_doubleClicked(const QModelIndex &index)
{
    QString val = index.data().toString();
    if(val.contains('='))
    {
        for(int i = 0; i < val.size(); ++i)
        {
            if(val.at(i) == '=')
            {
                val.remove(i, 1);
            }
        }
    }

    QString oldText = ui->lineEditInput->text();
    ui->lineEditInput->setText(oldText + val);
}
