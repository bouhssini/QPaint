#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->wSa, SIGNAL(chimage(QByteArray,QString)), this,SLOT( chimage(QByteArray, QString) ) );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chimage(QByteArray bzip, QString hMD5)
{
    ui->wSa->Imageunzip(bzip);
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    ui->wSa->Setvw(checked);
}

