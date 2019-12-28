#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wsbora.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void chimage(QByteArray bzip, QString hMD5);
    void on_checkBox_clicked(bool checked);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
