#include "wsbora.h"
#include "ui_wsbora.h"
#include "nightcharts.h"
#include <QFont>
#include <QDebug>
#include <QtGui>
#include <QCursor>
#include <QColorDialog>

wSbora::wSbora(QWidget *parent) :  QWidget(parent),
    ui(new Ui::wSbora),
    sel_B(false), sel_M(false),Dcopy(false),
    colorBackground(Qt::transparent),
    PicBackground(":/images/blackborad.png"),
    imgType("png"),PenSize(6),
    colorChoix(Qt::red)
{
    ui->setupUi(this);
    connect(ui->mB_clip, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_cls, SIGNAL(toggled(bool)),  this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_pen, SIGNAL(toggled(bool)),  this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_text, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_fill, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_line, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_pip, SIGNAL(toggled(bool)),  this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_spr, SIGNAL(toggled(bool)),  this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_rec, SIGNAL(toggled(bool)),  this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_sel, SIGNAL(toggled(bool)),  this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_mv, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));


    clearpix();
    bt_pres = "mB_pen";
    SetColorChoix(colorChoix);
    ui->spinBox->setValue(PenSize);
}

void wSbora::on_mB_toggled(bool)
{
    ui->label->setFocus();
    QToolButton* mB = dynamic_cast<QToolButton*>(sender());
    if (bt_pres == "mB_sel" || bt_pres == "mB_rec" || bt_pres == "mB_clip" ){
        QPainter painter(&pix);
        painter.drawPixmap(x_tm,y_tm,tmp);
        pixsel.fill(Qt::transparent);
        mv_x = 0;mv_y = 0;
        sel_M = false;sel_B = false;
    }
   // QCursor cursorTarget = QCursor(   mB->icon().pixmap(mB->icon().actualSize(QSize(64, 64))),-32,-32   );
   // ui->label->setCursor(cursorTarget);
    bt_pres = mB->objectName();
    ui->label_3->setText(bt_pres);
    damj();
}
void wSbora::on_mB_mbyan_clicked()
{
     MByan();
}

void wSbora::paintEvent(QPaintEvent *e)
{

}

wSbora::~wSbora()
{
    delete ui;
}

void wSbora::MByan()
{
    //pix = QPixmap(ui->label->width(),ui->label->height());
    //pix.fill(colorBackground);//(Qt::white);//
    //pix.fill(Qt::transparent);
    QPainter painter(&pix);

    Nightcharts PieChart;

    PieChart.setType(Nightcharts::Dpie);//{Histogramm,Pie,Dpie};
    PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical,Horizontal}
    PieChart.setCords(120,50,ui->label->width()/2,ui->label->height()/3);
    PieChart.addPiece("المجموع العام السنوي",QColor(150,10,50),44);
    PieChart.addPiece("علي",Qt::green,27);
    PieChart.addPiece("كمال",Qt::cyan,4);
    PieChart.addPiece("عمر",Qt::yellow,7);
    PieChart.addPiece("ابو بكر",Qt::blue,4);
    PieChart.addPiece("طلحة",Qt::red,14);
    //PieChart.setShadows(false);
    PieChart.draw(&painter);
    PieChart.drawLegend(&painter);
    damj();
    on_pushButton_5_clicked();
}

void wSbora::damj()
{
    QPixmap pixtmp = QPixmap(ui->label->width(),ui->label->height());
    pixtmp.fill(Qt::transparent);
    QPainter painter(&pixtmp);
    painter.setBrush(QBrush(PicBackground));
    painter.drawRect(0, 0,pix.width(),pix.height());
    painter.drawPixmap(0,0,pix);
    painter.drawPixmap(0,0,pixsel);
    ui->label->setPixmap(pixtmp);
}

void wSbora::damjview(QByteArray bArray)
{
    QByteArray by = qUncompress(bArray);
    QPixmap p;
    p.loadFromData(by,imgType.toStdString().c_str());
    QPixmap pixtmp = QPixmap(ui->LaView->width(),ui->LaView->height());
    pixtmp.fill(Qt::transparent);
    QPainter painter(&pixtmp);
    painter.setBrush(QBrush(PicBackground));
    painter.drawRect(0, 0,p.width(),p.height());
    painter.drawPixmap(0,0,p);
    //painter.drawPixmap(0,0,pixsel);
    ui->LaView->setPixmap(pixtmp);
}

void wSbora::clearpix()
{
    pix = QPixmap(ui->label->width(),ui->label->height());
    pix.fill(Qt::transparent);
    pixsel = pix.copy(0,0,pix.width(),pix.height());
    damj();
    x=0;y=0;
    prss = false;
}

void wSbora::drawLine()
{
    pixsel = QPixmap(ui->label->width(),ui->label->height());
    pixsel.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pixsel);
    painter.setPen(QPen(colorChoix,PenSize ,
                        Qt::SolidLine,
                        Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(x,y ,ui->label->x, ui->label->y);
    damj();
}
void wSbora::drawPen()
{
    QPainter painter;
    painter.begin(&pix);
    painter.setPen(QPen(colorChoix,PenSize ,
                        Qt::SolidLine,
                        Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(x,y ,ui->label->x, ui->label->y);
    x = ui->label->x;
    y = ui->label->y;
    damj();
}
void wSbora::drawSel()
{
    int     lb_x = ui->label->x ,
            lb_y = ui->label->y;
    pixsel = QPixmap(ui->label->width(),ui->label->height());
    pixsel.fill(Qt::transparent);
    QPainter painter(&pixsel);
    if(bt_pres == "mB_sel")
        painter.setPen(QPen(Qt::white, 1, Qt::DashLine));
    else
        painter.setPen(QPen(colorChoix, PenSize, Qt::SolidLine));

   // painter.setBrush(Qt::NoBrush);

    if (bt_pres == "mB_clip")
        painter.drawEllipse(x, y,lb_x-x, lb_y-y);
    else if (bt_pres == "mB_sel"){
        painter.drawRect(x, y,lb_x-x, lb_y-y);
        painter.setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter.drawRect(x+1, y+1,lb_x-x-2, lb_y-y-2);
    }else
        painter.drawRect(x, y,lb_x-x, lb_y-y);

    tstRec(x,y,lb_x,lb_y);
    x_tm=sel_x - PenSize;
    y_tm=sel_y - PenSize;
    damj();
}
void wSbora::drawCls()
{
    QPainter painter;
    painter.begin(&pix);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.setPen(QPen(colorBackground,PenSize ,Qt::SolidLine ,Qt::RoundCap ,Qt::RoundJoin));
    painter.drawLine(x,y ,ui->label->x, ui->label->y);
    painter.end();
    x = ui->label->x;
    y = ui->label->y;
    damj();
}
void wSbora::drawMv()
{
    pixsel = QPixmap(ui->label->width(),ui->label->height());
    pixsel.fill(Qt::transparent);
    QPainter painter(&pixsel);
    x_tm = sel_x + (x - mv_x) - PenSize;
    y_tm = sel_y + (y - mv_y) - PenSize;
    painter.drawPixmap(x_tm,y_tm,tmp);

    if(bt_pres == "mB_sel"){
        painter.setPen(QPen(Qt::white, 1, Qt::DashLine));
        painter.setBrush(Qt::transparent);
        painter.drawRect(x_tm,y_tm,sel_w,sel_h);
        painter.setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter.drawRect(x_tm+1,y_tm+1,sel_w-2,sel_h-2);
    }

    x = ui->label->x;
    y = ui->label->y;
    damj();
}

void wSbora::drawpip()
{
    QImage img = pix.toImage();
    x = ui->label->x;
    y = ui->label->y;
    QRgb pixel(img.pixel(x,y));
    QColor tmpColor(pixel);
    SetColorChoix(tmpColor);

}

void wSbora::drawFill()
{
    QColor switchColor = colorChoix;
    QImage img = pix.toImage();

    x = ui->label->x;
    y = ui->label->y;

    QRgb pixel(img.pixel(x,y));
    QColor oldColor(pixel);

    if(switchColor != oldColor)
    {
        fillRecurs(x, y, switchColor.rgb(), oldColor.rgb(),img);
        pix = QPixmap::fromImage(img);
        damj();
    }
}

void wSbora::SetColorChoix(QColor co)
{
    colorChoix = co;
    QPixmap p = QPixmap(ui->lacolor->width(),ui->lacolor->height());
    p.fill(colorChoix);
    ui->lacolor->setPixmap(p);
}

QColor wSbora::ColorChoix()
{
    return colorChoix;
}

void wSbora::on_label_mouse_Press()
{
    ui->label_3->setText("Press");
    prss = true;
    x = ui->label->x;
    y = ui->label->y;

}
void wSbora::on_label_mouse_Move()
{
    ui->label_3->setText("Move");
    ui->label_2->setText(QString("x : %1 , y : %2")  .arg(ui->label->x)  .arg(ui->label->y));
    if (prss){
        if(bt_pres       == "mB_pen"){
            drawPen();
        }else if(bt_pres == "mB_line"){
            drawLine();
        }else if(bt_pres == "mB_sel" || bt_pres == "mB_rec" || bt_pres == "mB_clip"){
            if (sel_B){
                sel_B = false;

                if (tstCus()){
                    mv_x = x + 1;
                    mv_y = y + 1;
                    sel_M = true;
                }else{
                    QPainter painter(&pix);
                    painter.drawPixmap(x_tm,y_tm,tmp);
                }
            }else if(sel_M){
                drawMv();
            }else
                drawSel();
        }else if(bt_pres == "mB_cls"){
            drawCls();
        }
    }
}
void wSbora::on_label_mouse_Release()
{
    int n = PenSize *2;
    ui->label_3->setText("Release");
    prss = false;
    if (sel_M){
        int xx = sel_x + (x - mv_x),yy = sel_y + (y - mv_y);
        tstRec(xx,yy,sel_w+xx,sel_h+yy);
    }

    if (bt_pres == "mB_sel" && sel_B == false ){
        sel_B = true;
        if (sel_M == false){
            tmp = pix.copy(sel_x,sel_y,sel_w,sel_h);

            if (!Dcopy)
            {
                QPainter painter(&pix);
                painter.setCompositionMode (QPainter::CompositionMode_Source);
                painter.fillRect(sel_x,sel_y,sel_w,sel_h,colorBackground);
                painter.setCompositionMode (QPainter::CompositionMode_SourceOver);
            }
//----------------إظهار التحديد ----------------
            QPixmap tmp2 = pixsel;
            QPainter painter2(&pixsel);
            painter2.drawPixmap(sel_x,sel_y,tmp);
            painter2.drawPixmap(0,0,tmp2);
//-------------------------------------------------------

            x_tm += PenSize;
            y_tm += PenSize;
        }
    }
    if (bt_pres == "mB_rec" && sel_B == false ){
        sel_B = true;
        if (sel_M == false){

            tmp = QPixmap(sel_w+n,sel_h+n);
            tmp.fill(Qt::transparent);
            QPainter painter(&tmp);
            painter.setPen(QPen(colorChoix, PenSize, Qt::SolidLine));
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(PenSize,PenSize,sel_w,sel_h);
            mv_x -=  PenSize;
            mv_y -=  PenSize;
        }
    }
    if (bt_pres == "mB_clip" && sel_B == false ){
        sel_B = true;
        if (sel_M == false){

            tmp = pix.copy(sel_x,sel_y,sel_w+n,sel_h+n);
            tmp.fill(Qt::transparent);
            QPainter painter(&tmp);
            painter.setPen(QPen(colorChoix, PenSize, Qt::SolidLine));
            painter.setBrush(Qt::NoBrush);
            painter.drawEllipse(PenSize,PenSize,sel_w,sel_h);
            mv_x -=  PenSize;
            mv_y -=  PenSize;
        }
    }
    if (bt_pres == "mB_line" ){
            QPainter painter(&pix);
            painter.setPen(QPen(colorChoix,PenSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(x,y ,ui->label->x, ui->label->y);
            pixsel = QPixmap(ui->label->width(),ui->label->height());
            pixsel.fill(Qt::transparent);
    }


    sel_M = false;

    if (bt_pres == "mB_fill"){
        drawFill();
    }
     if(bt_pres == "mB_pip"){
         drawpip();
     }
    on_pushButton_5_clicked();
}
void wSbora::on_label_mouse_leave()
{
    ui->label_3->setText("leave");
    prss = false;
    sel_M = false;
}

void wSbora::on_pushButton_5_clicked()
{
    QCryptographicHash* hash;
    QByteArray bArray;
    QBuffer buffer( &bArray );
    buffer.open( QIODevice::WriteOnly );
    //pix.save( &buffer, imgType,9 );
    QPixmap pixtmp = QPixmap(pix.width(),pix.height());
    pixtmp.fill(Qt::transparent);
    QPainter painter(&pixtmp);
    painter.drawRect(0, 0,pix.width(),pix.height());
    painter.drawPixmap(0,0,pix);
    painter.drawPixmap(0,0,pixsel);
    pixtmp.save( &buffer, imgType.toStdString().c_str(),9 );
    //pix.loadFromData(bArray,imgType);

    QByteArray by2 = qCompress(bArray,9); //qUncompress(by); //
    QByteArray result = hash->hash(bArray,QCryptographicHash::Md5);
    ui->label_5->setText(QString::number(bArray.size())+"  :  "+QString::number(by2.size()));
    ui->label_6->setText(result.toHex());
    buffer.close();
    damjview(by2);
}

void wSbora::on_pushButton_2_clicked()
{
    pix.save("gg."+imgType);
    clearpix();
}
void wSbora::on_pushButton_4_clicked()
{
    CancelSel();
}

void wSbora::CancelSel()
{
    QPainter painter(&pix);
    painter.drawPixmap(x_tm,y_tm,tmp);
    pixsel.fill(Qt::transparent);
    mv_x = 0;mv_y = 0;
    sel_M = false;sel_B = false;
    damj();
    on_pushButton_5_clicked();
}

void wSbora::DeleteSel()
{
    pixsel.fill(Qt::transparent);
    mv_x = 0;mv_y = 0;
    sel_M = false;sel_B = false;
    tmp.fill(Qt::transparent);
    damj();
    on_pushButton_5_clicked();
}

void wSbora::on_lacolor_mouse_Press()
{
    QColorDialog d;
    QColor c = d.getColor(ColorChoix());
    SetColorChoix(c);
}

void wSbora::fillRecurs(int x, int y, QRgb switchColor, QRgb oldColor, QImage &tempImage)
{
    int temp_x(x), left_x(0);
    while(true)
    {
        if(tempImage.pixel(temp_x, y) != oldColor)
            break;
        tempImage.setPixel(temp_x, y, switchColor);
        if(temp_x > 0)
        {
            --temp_x;
            left_x = temp_x;
        }
        else
            break;
    }

    int right_x(0);
    temp_x = x + 1;
    while(true)
    {
        if(tempImage.pixel(temp_x, y) != oldColor)
            break;
        tempImage.setPixel(temp_x, y, switchColor);
        if(temp_x < tempImage.width() - 1)
        {
            temp_x++;
            right_x = temp_x;
        }
        else
            break;
    }

    for(int x_(left_x+1); x_ < right_x; ++x_)
    {
        if(y < 1 || y >= tempImage.height() - 1)
            break;
        if(right_x > tempImage.width())
            break;
        QRgb currentColor = tempImage.pixel(x_, y - 1);
        if(currentColor == oldColor && currentColor != switchColor)
            fillRecurs(x_, y - 1, switchColor, oldColor, tempImage);
        currentColor = tempImage.pixel(x_, y + 1);
        if(currentColor == oldColor && currentColor != switchColor)
            fillRecurs(x_, y + 1, switchColor, oldColor, tempImage);
    }
}
bool wSbora::tstCus()
{
    int     lb_x = ui->label->x ,
            lb_y = ui->label->y ;

    if (lb_x > sel_x && lb_x < sel_x + sel_w && lb_y > sel_y && lb_y < sel_y + sel_h)
        {
            return true;
        }else{
            return false;
        }
}
void wSbora::tstRec(int x1, int y1, int x2, int y2)
{
    sel_x = tstVal(x1,x2,false);
    sel_w = tstVal(x1,x2,true) - sel_x;
    sel_y = tstVal(y1,y2,false);
    sel_h = tstVal(y1,y2,true) - sel_y;

    ui->label_4->setText(QString("x : %1\ny : %2\nwt : %3\nht : %4")
                         .arg(sel_x)
                         .arg(sel_y)
                         .arg(sel_w)
                         .arg(sel_h));
}

void wSbora::on_spinBox_valueChanged(int arg1)
{
    PenSize = arg1;
}

void wSbora::on_pushButton_3_clicked()
{
    QPixmap page = QPixmap(":/images/page.jpg");
    QPainter painter(&pix);
    painter.drawPixmap(0,0,page.copy(0,0,pix.width(),pix.height()));
    damj();
}

void wSbora::on_label_key_Press(QKeyEvent *e)
{
    //qDebug() << "keyPressEvent:" << e->key();
    switch (e->key()) {
    case Qt::Key_Alt:
         Dcopy = true;
        break;
    default:
        Dcopy = false;
        break;
    }

}

void wSbora::on_label_key_Release(QKeyEvent *e)
{

    //qDebug() << "keyReleaseEvent:" << e->key();
    Dcopy = false;
    switch (e->key()) {
    case Qt::Key_Delete:
         DeleteSel();
        break;
    case Qt::Key_Escape:
         CancelSel();
        break;
    default:
        Dcopy = false;
        break;
    }
}




