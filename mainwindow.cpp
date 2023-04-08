#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datalist.h"
#include "filereader.h"
#include <QFileDialog>
#include <string>
#include <fstream>
#include <QTextStream>
#include <QMessageBox>
#include <QScrollBar>
#include <QException>
#define TEST
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->_pathForFile = "";
    ui->setupUi(this);
    ui->spinBox->setValue(1);
    this->ui->tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal {border: 2px grey;background: #32CC99; height: 25px;}");

#ifdef TEST
    QPixmap bkgnd("D:\\QtLearning\\chartTest\build-DataAnalysis-Desktop_Qt_6_4_2_MinGW_64_bit-Debug\\Grey-paper.png");
        //bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
#endif

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_2_clicked()
{
    this->ui->tableWidget->reset();
    this->ui->tableWidget->clear();
    list = new DataList();
    this->_pathForFile = QFileDialog::getOpenFileName(this, "Choose datas", "C:\\");
    QVector<std::string> vector;
    FileReader reader;
    reader.SetOutput(vector);
    reader.SetPath(this->_pathForFile.toStdString());
    reader.ReadFromFile();
    int columnCountTable = vector.length() / this->ui->spinBox->value();
    int counterOverStep = this->ui->spinBox->value();
    try {
    for(int i = 0; i < this->ui->spinBox->value(); i++){
        QVector<float> *tempVect = new QVector<float>();
        for(int j = i; j < vector.length(); j+=counterOverStep){
            tempVect->push_back(std::stof(vector[j]));
        }
        list->push_back(i, *tempVect);
    }
    this->ui->tableWidget->setColumnCount(columnCountTable);
    this->ui->tableWidget->setRowCount(this->ui->spinBox->value());
    for(int i = 0; i < this->ui->spinBox->value(); i++){
        for(int j = 0; j < columnCountTable; j++){
            this->ui->tableWidget->setItem(i,j, new QTableWidgetItem(QString::number(this->list->at(i,j))));
        }
    }

    }catch(QException &ex){
        QMessageBox *exceptionMBox = new QMessageBox(this);
        exceptionMBox->setText("Some exception with filling data has been occured\nu can find more information in log file");
        exceptionMBox->show();
        exceptionMBox->open();
        QFile exceptionLog;
        if(exceptionLog.open(QFile::WriteOnly | QFile::Append)){
            exceptionLog.write(ex.what());
        }
    }
}

