#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datalist.h"
#include "filereader.h"
#include <QFileDialog>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->_pathForFile = "";
    ui->setupUi(this);


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
    DataList list = DataList();
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
    list.push_back(0, tempA);
    list.push_back(1, tempB);
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < tempA.size() - 1; j++){
            this->ui->tableWidget->setItem(i,j, new QTableWidgetItem(QString::number(list.at(i,j))));
        }
    }
}

