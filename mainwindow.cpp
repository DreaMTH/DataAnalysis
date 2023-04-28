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
#include <QKeyEvent>
#define TEST
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /*startUp programm preparing....*/
    this->_pathForFile = "";
    this->ui->setupUi(this);
    this->ui->spinBox->setValue(1);
    this->ui->spinBox->setMinimum(1);
    this->ui->spinBox_2->setValue(1);
    this->ui->spinBox_2->setMinimum(1);
    this->ui->spinBox_2->setMaximum(4);
    this->ui->spinBox->setToolTip("Amount of vecters");
    this->ui->spinBox_2->setToolTip("Number of single vector for reading");
    this->ui->stackedWidget->setCurrentIndex(0);
    this->ui->plainTextEdit->setPlainText("Test message");
    this->ui->fxPlot->setInteraction(QCP::iRangeZoom);
    this->ui->fxPlot->setInteraction(QCP::iRangeDrag);
    this->ui->histoPlot->setInteraction(QCP::iRangeDrag);
    this->ui->histoPlot->setInteraction(QCP::iRangeZoom);
    this->ui->tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {	border: none;    background: rgb(45, 45, 68);    width: 14px;    margin: 15px 0 15px 0;	border-radius: 0px; }QScrollBar::handle:vertical {		background-color: rgb(80, 80, 122);	min-height: 30px;	border-radius: 7px;}QScrollBar::handle:vertical:hover{		background-color: rgb(255, 0, 127);}QScrollBar::handle:vertical:pressed {		background-color: rgb(185, 0, 92);}QScrollBar::sub-line:vertical {	border: none;	background-color: rgb(59, 59, 90);	height: 15px;	border-top-left-radius: 7px;	border-top-right-radius: 7px;	subcontrol-position: top;	subcontrol-origin: margin;}QScrollBar::sub-line:vertical:hover {		background-color: rgb(255, 0, 127);}QScrollBar::sub-line:vertical:pressed {		background-color: rgb(185, 0, 92);}/* BTN BOTTOM - SCROLLBAR */QScrollBar::add-line:vertical {	border: none;	background-color: rgb(59, 59, 90);	height: 15px;	border-bottom-left-radius: 7px;	border-bottom-right-radius: 7px;	subcontrol-position: bottom;	subcontrol-origin: margin;}QScrollBar::add-line:vertical:hover {		background-color: rgb(255, 0, 127);}QScrollBar::add-line:vertical:pressed {		background-color: rgb(185, 0, 92);}QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {	background: none;}QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {	background: none;}");
    this->ui->tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal {	border: none;    background: rgb(45, 45, 68);    height: 14px;    margin: 0 15px 0 15px;	border-radius: 0px; }QScrollBar::handle:horizontal {		background-color: rgb(80, 80, 122);	min-width: 30px;	border-radius: 7px;}QScrollBar::handle:horizontal:hover{		background-color: rgb(255, 0, 127);}QScrollBar::handle:horizontal:pressed {		background-color: rgb(185, 0, 92);}QScrollBar::sub-line:horizontal {	border: none;	background-color: rgb(59, 59, 90);	width: 15px; border-top-left-radius: 7px; border-bottom-left-radius: 7px;	subcontrol-position: left;	subcontrol-origin: margin;}QScrollBar::sub-line:horizontal:hover {		background-color: rgb(255, 0, 127);}QScrollBar::sub-line:horizontal:pressed {		background-color: rgb(185, 0, 92);}QScrollBar::add-line:horizontal {	border: none;	background-color: rgb(59, 59, 90);	width: 15px;	border-top-right-radius: 7px;	border-bottom-right-radius: 7px;	subcontrol-position: right;	subcontrol-origin: margin;}QScrollBar::add-line:horizontal:hover {		background-color: rgb(255, 0, 127);}QScrollBar::add-line:horizontal:pressed {		background-color: rgb(185, 0, 92);}QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal {	background: none;}QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {	background: none;}");
    this->ui->plainTextEdit->verticalScrollBar()->setStyleSheet(this->ui->tableWidget->verticalScrollBar()->styleSheet());
    this->ui->plainTextEdit->horizontalScrollBar()->setStyleSheet(this->ui->tableWidget->horizontalScrollBar()->styleSheet());
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
        connect(this->ui->pushButton_3, &QPushButton::clicked, this, [=]() {
            ui->stackedWidget->setCurrentIndex(0);
    });

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
    this->ui->spinBox_2->setMaximum(this->ui->spinBox->value());
    list = new DataList();
    this->_pathForFile = QFileDialog::getOpenFileName(this, "Choose datas", "C:\\");
    if(_pathForFile.isEmpty()){
        QMessageBox emptyPathMessage;
        emptyPathMessage.setText("File wasnt chosen");
        emptyPathMessage.setIcon(QMessageBox::Information);
        emptyPathMessage.setGeometry(this->width()/2, this->height() / 2, 356, 256);
        emptyPathMessage.exec();
        return;
    }
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
    this->plotGraphs();
    this->ApploadData();
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


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->key();
    switch (event->key()) {
    case Qt::Key_R:
        if(event->modifiers().testFlag(Qt::ControlModifier)){
            this->plotGraphs();
        }
        break;
    case Qt::Key_Return | Qt::Key_Enter:
        if(event->modifiers().testFlag(Qt::AltModifier)){

            if(!this->isFullScreen()){
                this->setWindowState(Qt::WindowFullScreen);
            }else{
                this->setWindowState(Qt::WindowNoState);
            }
        }
        break;
    default:
        break;
    }
}

void MainWindow::plotGraphs()
{
    this->ui->histoPlot->clearPlottables();
    this->ui->fxPlot->clearPlottables();
    int currentVector = this->ui->spinBox_2->value() - 1;
    auto values = list->GetClassesAt(currentVector);
    auto Prob = list->histoBulding(currentVector);
    this->myBars = new QCPBars(this->ui->histoPlot->xAxis, this->ui->histoPlot->yAxis);
    for(int i = 0; i < values.length(); i++){
        this->myBars->addData((double)values[i], (double)Prob[i]);
    }
    this->myBars->setWidth(list->GetH().at(currentVector));
    this->myBars->setBrush(QBrush(QColor(255, 0, 127, 33)));
    this->ui->histoPlot->rescaleAxes();
    this->ui->histoPlot->replot();
    QVector<QVector<QPointF> > buildModel = *new QVector<QVector<QPointF> >(values.length());
    float x1;
    float y1 = Prob[0];
    float min = *std::min_element((*this->list)[currentVector].begin(), (*this->list)[currentVector].end());
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

void MainWindow::ApploadData()
{
    this->ui->plainTextEdit->clear();  
    for(int i = 0; i < this->list->Size(); i++){
        this->ui->plainTextEdit->appendPlainText(this->ConcatinatingDatas(i));
    }


}

QString MainWindow::ConcatinatingDatas(const int index)
{
    return QString("%0 Vecter Params:\n\tMu = %1\n\tSigma = %2\n\tMedian = %3\n\tMAD = %4\n\tAssymetry Coefficient = %5\n\tExcess Coefficient = %6\n\tIntervals:\n\t\t%7 < σ(x) <%8\n\t\t%9 < σ(S) < %10\n\t\t")
        .arg(index).arg(this->list->MuAt(index)).arg(this->list->SigmaAt(index))
        .arg(this->list->Median(index)).arg(this->list->MAD(index)).arg(this->list->AssymetryCoef(index)).arg(this->list->ExscessCoef(index))
        .arg(this->list->Kvant(index).at(0)).arg(this->list->Kvant(index).at(1)).arg(this->list->Kvant(index).at(2)).arg(this->list->Kvant(index).at(3));
}

