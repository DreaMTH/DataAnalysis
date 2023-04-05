#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datalist.h"
#include "filereader.h"
#include <QFileDialog>
#include <string>
#define TEST
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->_pathForFile = "";
    ui->setupUi(this);
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
    this->ui->tableWidget->setColumnCount(tempA.size());
    this->ui->tableWidget->setRowCount(2);
    this->list->push_back(0, tempA);
    this->list->push_back(1, tempB);

    for(int i = 0; i < this->list->Size(); i++){
        for(int j = 0; j < tempA.size(); j++){
            this->ui->tableWidget->setItem(i,j, new QTableWidgetItem(QString::number(this->list->at(i,j))));
        }
    }

}

