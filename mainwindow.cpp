#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), startUp(false)
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
    if (!startUp){
        startUp = true;
        hashMD5 = hMD5;
        //ui->wSa->Imageunzip(bzip);
        qDebug() << "bzip: " << bzip.size() ;

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

        QUrl url("http://66.70.190.62/web/upload/up.php");
        QNetworkRequest request(url);

        QNetworkAccessManager * manager = new QNetworkAccessManager();
        reply = manager->post(request, multiPart);
        multiPart->setParent(reply); // delete the multiPart with the reply
        connect(reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(Progress(qint64,qint64)));
        connect(reply, SIGNAL(finished()), this, SLOT(uploadDone()));
        /*-------------------------------------------------------------------------*/
    }

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

void MainWindow::uploadDone()
{
    QString txt;
    int nu = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (nu == 200){
        txt = "Finished: " + QString::number( nu ) + "\n";
        txt += reply->readAll().trimmed();
        //ui->label->setText("");

    }else{
        txt = "Error: " + reply->errorString() + " nu:" + QString::number( nu ) + "\n";
    }
    qDebug() << txt;


    reply->deleteLater();
    startUp = false;


    QNetworkReply *rr;
    QNetworkAccessManager *mgr;
    QNetworkRequest req;

    QUrl url("http://66.70.190.62/web/upload/images/"+hashMD5);

    mgr = new QNetworkAccessManager(this);
    req.setUrl(url);
    rr = mgr->get(req);
    QEventLoop loop;
    connect(rr, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QByteArray bzip = rr->readAll();
    nu = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (nu == 200){
        ui->wSa->Imageunzip(bzip);
    }
    rr->deleteLater();
    mgr->deleteLater();
}
