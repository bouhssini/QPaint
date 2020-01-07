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

void MainWindow::Senthash()
{
   // ui->progressBar->setValue(0);


}

void MainWindow::AddPart(QHttpMultiPart *multiPart, QString name, QByteArray by)
{
    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\""+name+"\""));
    textPart.setBody(by);
    multiPart->append(textPart);
}

void MainWindow::chimage(QByteArray bzip, QString hMD5)
{
    ui->wSa->Imageunzip(bzip);

    /*-------------------------------------------------------------------------*/
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    AddPart(multiPart,"id_usr","1");
    AddPart(multiPart,"id_room","20");

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/*"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant("form-data; name=\"userImage\";  filename=\""+hMD5+"\""));

    imagePart.setBody(bzip);

    multiPart->append(imagePart);

    QUrl url("http://66.70.190.62/web/upload/upload.php");
    QNetworkRequest request(url);

    QNetworkAccessManager * manager = new QNetworkAccessManager();
    reply = manager->post(request, multiPart);
    multiPart->setParent(reply); // delete the multiPart with the reply
    connect(reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(Progress(qint64,qint64)));
    connect(reply, SIGNAL(finished()), this, SLOT(uploadDone()));
    /*-------------------------------------------------------------------------*/


}

void MainWindow::on_checkBox_clicked(bool checked)
{
    ui->wSa->Setvw(checked);
}

void MainWindow::Progress(qint64 bytesSent, qint64 bytesTotal) {
    qreal n = (qreal)bytesSent/(qreal)bytesTotal;
    //ui->progressBar->setValue(n * 100);
    qDebug() << "Uploaded " << bytesSent << " of " << bytesTotal;
}
