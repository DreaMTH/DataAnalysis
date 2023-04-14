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
    this->ui->setupUi(this);
    this->ui->spinBox->setValue(1);
    this->ui->fxPlot->setInteraction(QCP::iRangeZoom);
    this->ui->fxPlot->setInteraction(QCP::iRangeDrag);
    this->ui->histoPlot->setInteraction(QCP::iRangeDrag);
    this->ui->histoPlot->setInteraction(QCP::iRangeZoom);
    this->ui->tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal {border: 2px grey;background: #32CC99; height: 25px;}");
    this->ui->tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {	border: none;    background: rgb(45, 45, 68);    width: 14px;    margin: 15px 0 15px 0;	border-radius: 0px; }QScrollBar::handle:vertical {		background-color: rgb(80, 80, 122);	min-height: 30px;	border-radius: 7px;}QScrollBar::handle:vertical:hover{		background-color: rgb(255, 0, 127);}QScrollBar::handle:vertical:pressed {		background-color: rgb(185, 0, 92);}QScrollBar::sub-line:vertical {	border: none;	background-color: rgb(59, 59, 90);	height: 15px;	border-top-left-radius: 7px;	border-top-right-radius: 7px;	subcontrol-position: top;	subcontrol-origin: margin;}QScrollBar::sub-line:vertical:hover {		background-color: rgb(255, 0, 127);}QScrollBar::sub-line:vertical:pressed {		background-color: rgb(185, 0, 92);}/* BTN BOTTOM - SCROLLBAR */QScrollBar::add-line:vertical {	border: none;	background-color: rgb(59, 59, 90);	height: 15px;	border-bottom-left-radius: 7px;	border-bottom-right-radius: 7px;	subcontrol-position: bottom;	subcontrol-origin: margin;}QScrollBar::add-line:vertical:hover {		background-color: rgb(255, 0, 127);}QScrollBar::add-line:vertical:pressed {		background-color: rgb(185, 0, 92);}QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {	background: none;}QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {	background: none;}");
    this->ui->tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal {	border: none;    background: rgb(45, 45, 68);    height: 14px;    margin: 0 15px 0 15px;	border-radius: 0px; }QScrollBar::handle:horizontal {		background-color: rgb(80, 80, 122);	min-width: 30px;	border-radius: 7px;}QScrollBar::handle:horizontal:hover{		background-color: rgb(255, 0, 127);}QScrollBar::handle:horizontal:pressed {		background-color: rgb(185, 0, 92);}QScrollBar::sub-line:horizontal {	border: none;	background-color: rgb(59, 59, 90);	width: 15px; border-top-left-radius: 7px; border-bottom-left-radius: 7px;	subcontrol-position: left;	subcontrol-origin: margin;}QScrollBar::sub-line:horizontal:hover {		background-color: rgb(255, 0, 127);}QScrollBar::sub-line:horizontal:pressed {		background-color: rgb(185, 0, 92);}QScrollBar::add-line:horizontal {	border: none;	background-color: rgb(59, 59, 90);	width: 15px;	border-top-right-radius: 7px;	border-bottom-right-radius: 7px;	subcontrol-position: right;	subcontrol-origin: margin;}QScrollBar::add-line:horizontal:hover {		background-color: rgb(255, 0, 127);}QScrollBar::add-line:horizontal:pressed {		background-color: rgb(185, 0, 92);}QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal {	background: none;}QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {	background: none;}");
#ifdef TEST
    QPixmap bkgnd("D:\\QtLearning\\chartTest\build-DataAnalysis-Desktop_Qt_6_4_2_MinGW_64_bit-Debug\\Grey-paper.png");
        //bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
        this->ui->fxPlot->setMouseTracking(true);
        connect(this->ui->fxPlot, SIGNAL(mouseMove(QMouseEvent*)),this, SLOT(setToolTipFx(QMouseEvent*)));
        this->ui->fxPlot->setMouseTracking(true);
        connect(this->ui->histoPlot, SIGNAL(mouseMove(QMouseEvent*)),this, SLOT(setToolTipHysto(QMouseEvent*)));
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
    this->ui->histoPlot->clearPlottables();
    this->ui->fxPlot->clearPlottables();
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
    qDebug() << list[0][0];
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
    auto values = list->GetClassesAt(0);
    auto Prob = list->histoBulding(0);
    QCPBars *myBars = new QCPBars(this->ui->histoPlot->xAxis, this->ui->histoPlot->yAxis);
    for(int i = 0; i < values.length(); i++){
        myBars->addData((double)values[i], (double)Prob[i]);
    }
    myBars->setWidth(list->GetH().at(0));
    this->ui->histoPlot->rescaleAxes();
    this->ui->histoPlot->replot();
    QVector<QVector<QPointF> > buildModel = *new QVector<QVector<QPointF> >(values.length());
    float x1;
    float y1 = Prob[0];
    float min = *std::min_element(list[0][0].begin(), list[0][0].end());
    for(int i = 0; i < values.length(); i++){
        if(i != 0){
            y1 += Prob[i];
            x1 = values[i-1];
            buildModel[i].push_back(*new QPointF(x1, y1));
            x1 = values[i];
            if(i < values.length() - 1){
                buildModel[i].push_back(*new QPointF(x1, y1));
            }
        }else{
            buildModel[i].push_back(*new QPointF(min, y1));
            buildModel[i].push_back(*new QPointF(values[i], y1));
        }
    }
    buildModel[values.length() - 1].push_back(*new QPointF(values.last(), y1));
    for(int i = 0; i < buildModel.length(); i++){
        this->ui->fxPlot->addGraph();
        for(int j = 0; j < buildModel[i].length(); j++){
            this->ui->fxPlot->graph(i)->addData(buildModel[i][j].x(), buildModel[i][j].y());
        }
    }
    this->ui->fxPlot->rescaleAxes();
    this->ui->fxPlot->replot();
}

void MainWindow::setToolTipFx(QMouseEvent *event)
{
    QToolTip::showText(*new QPoint(event->globalPosition().x(), event->globalPosition().y()-32),QString("%1, %2")
                       .arg(ui->fxPlot->xAxis->pixelToCoord(event->pos().x())).arg(ui->fxPlot->yAxis->pixelToCoord(event->pos().y())));
}

void MainWindow::setToolTipHysto(QMouseEvent *event)
{
    QToolTip::showText(*new QPoint(event->globalPosition().x(), event->globalPosition().y()-32),QString("%1, %2")
                       .arg(ui->histoPlot->xAxis->pixelToCoord(event->pos().x())).arg(ui->histoPlot->yAxis->pixelToCoord(event->pos().y())));
}

