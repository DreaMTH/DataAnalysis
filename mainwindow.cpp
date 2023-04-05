#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datalist.h"
#include "filereader.h"
#include <QFileDialog>
#include <string>
#include <fstream>
#include <QTextStream>
#define TEST
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->_pathForFile = "";
    ui->setupUi(this);
    ui->spinBox->setValue(1);
    list = new DataList();
#ifdef TEST

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

    this->_pathForFile = QFileDialog::getOpenFileName(this, "Choose datas", "C:\\");
    QVector<std::string> vector;
    FileReader reader;
    reader.SetOutput(vector);
    reader.SetPath(this->_pathForFile.toStdString());
    reader.ReadFromFile();
    int columnCountTable = vector.length() / this->ui->spinBox->value();
    /*
    QVector<float> tempA = *new QVector<float>();
    QVector<float> tempB = *new QVector<float>();
    for(int i = 0; i < vector.size(); i++){
        if(i % 2 == 0){
            tempA.push_back(std::stof(vector[i]));
        }else if(i % 2 != 0){
            tempB.push_back(std::stof(vector[i]));
        }else if(i == 0){
            tempA.push_back(std::stof(vector[i]));
        }
    }
    */
    int counterOverStep = this->ui->spinBox->value();
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

}

