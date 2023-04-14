#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datalist.h"
#include <QMouseEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void extracted(QVector<std::string> &vector);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void setToolTipFx(QMouseEvent*event);
    void setToolTipHysto(QMouseEvent*event);
protected:

private:
    Ui::MainWindow *ui;
    QString _pathForFile;
    DataList *list;
};
#endif // MAINWINDOW_H
