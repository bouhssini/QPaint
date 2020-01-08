#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wsbora.h"
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Senthash();
    void AddPart(QHttpMultiPart *multiPart,QString name, QByteArray by);

private slots:
    void chimage(QByteArray bzip, QString hMD5);
    void on_checkBox_clicked(bool checked);

    void Progress(qint64 bytesSent, qint64 bytesTotal);
    void uploadDone();

private:
    Ui::MainWindow *ui;

private:
    QNetworkReply * reply;
    bool startUp;
    QString hashMD5;
};

#endif // MAINWINDOW_H
