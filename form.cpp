#include "form.h"
#include "ui_form.h"
#include <QPixmap>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    pix = QPixmap(":/images/y.png");
    damj();
}

Form::~Form()
{
    delete ui;
}

int Form::tsthash(QPixmap pixtmp,int pos)
{
    QCryptographicHash* hash;
    QByteArray bArray;
    QBuffer buffer( &bArray );
    buffer.open( QIODevice::WriteOnly );

    pixtmp.save( &buffer, "PNG", 9 );

    QByteArray by2 = qCompress(bArray,9); //qUncompress(by); //
    QByteArray result = hash->hash(bArray,QCryptographicHash::Md5);
    buffer.close();
    //QByteArray result2 = hash->hash(by,QCryptographicHash::Md5);
    ui->txt->appendPlainText("pic:" + QString::number(pos) + " size:" + QString::number(by2.size()) + "\n- hash:" + result.toHex() + "\n" );
    return by2.size();
}

void Form::damj()
{
        QPixmap PicBackground(":/images/trans.jpg");

        QPixmap pixtmp = QPixmap(600,420);
        pixtmp.fill(Qt::transparent);
        QPainter painter(&pixtmp);
        painter.setBrush(QBrush(PicBackground));
        painter.drawRect(0, 0,600,420);
        painter.drawPixmap(0,0,pix);
        ui->la1->setPixmap(pixtmp);
}

void Form::damj2(QPixmap tmp)
{
        QPixmap PicBackground(":/images/trans.jpg");

        QPixmap pixtmp = QPixmap(600,420);
        pixtmp.fill(Qt::transparent);
        QPainter painter(&pixtmp);
        painter.setBrush(QBrush(PicBackground));
        painter.drawRect(0, 0,600,420);
        painter.drawPixmap(0,0,tmp);
        ui->la2->setPixmap(pixtmp);
}

void Form::on_pushButton_clicked()
{
    QPixmap pixtmp = QPixmap(600,420);
    pixtmp.fill(Qt::transparent);
    int x,y,w,h,tot;
    QPixmap p;

    QPainter painter;
    painter.begin(&pixtmp);

    w = 150;
    h = 105;
    tot = 0;

    //ui->txt->appendPlainText("pixmap:");
    // tsthash(pix);

    int ii = 0;
    for (int i = 0 ; i < 4; i++){
        for (int j = 0 ; j < 4; j++){
            x = i * w;
            y = j * h;
            ii++;
            p = pix.copy(x,y,w,h);
            painter.drawPixmap(x,y,p);
            tot += tsthash(p,ii);
        }
    }

    ui->txt->appendPlainText("\n total :" + QString::number(tot));


    damj2(pixtmp);
    pix = pixtmp;
damj();
}


void Form::on_pushButton_2_clicked()
{
    ui->txt->setPlainText("pixmap:");
    tsthash(pix,0);
}
