#include "dialog.h"
#include "ui_dialog.h"
#include "nightcharts.h"
#include <QFont>
#include <QDebug>
#include <QtGui>

Dialog::Dialog(QWidget *parent) :  QDialog(parent), ui(new Ui::Dialog), sel_B(false), sel_M(false)
{
    ui->setupUi(this);
    connect(ui->mB_clip, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_cls, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_pen, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_text, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_fill, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_line, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_pip, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_spr, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_rec, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));
    connect(ui->mB_sel, SIGNAL(toggled(bool)), this, SLOT(on_mB_toggled(bool)));
    clearpix();
    bt_pres = "mB_pen";
    colr = Qt::white;
}
void Dialog::paintEvent(QPaintEvent *e)
{

}
Dialog::~Dialog()
{
    delete ui;
}
void Dialog::damj()
{
    QPixmap pixtmp = QPixmap(ui->label->width(),ui->label->height());
    pixtmp.fill(Qt::transparent);
    QPainter painter(&pixtmp);
    painter.setBrush(QBrush(QPixmap(":/images/trans.jpg")));
    //painter.setBrush(Qt::white);
    painter.drawRect(0, 0,pix.width(),pix.height());
    painter.drawPixmap(0,0,pix);
    painter.drawPixmap(0,0,pixsel);
    ui->label->setPixmap(pixtmp);
}
void Dialog::clearpix()
{
    pix = QPixmap(ui->label->width(),ui->label->height());
    pix.fill(Qt::white);
    damj();
    x=0;y=0;
    prss = false;
}
void Dialog::drawPen()
{
    QPainter painter;
    painter.begin(&pix);
    painter.setPen(QPen(Qt::red,6 ,
                        Qt::SolidLine,
                        Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(x,y ,ui->label->x, ui->label->y);
    x = ui->label->x;
    y = ui->label->y;
    damj();
}
void Dialog::drawSel()
{
    int     lb_x = ui->label->x ,
            lb_y = ui->label->y;
    pixsel = QPixmap(ui->label->width(),ui->label->height());
    pixsel.fill(Qt::transparent);
    QPainter painter(&pixsel);
    painter.setPen(QPen(Qt::blue, 1, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(x, y,lb_x-x, lb_y-y);
    tstRec(x,y,lb_x,lb_y);
    x_tm=sel_x;
    y_tm=sel_y;
    damj();
}
void Dialog::drawCls()
{
    QPainter painter;
    painter.begin(&pix);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.setPen(QPen(colr,16 ,Qt::SolidLine ,Qt::RoundCap ,Qt::RoundJoin));
    painter.drawLine(x,y ,ui->label->x, ui->label->y);
    painter.end();
    x = ui->label->x;
    y = ui->label->y;
    damj();
}
void Dialog::drawMv()
{
    pixsel = QPixmap(ui->label->width(),ui->label->height());
    pixsel.fill(Qt::transparent);
    QPainter painter(&pixsel);
    x_tm = sel_x + (x - mv_x);
    y_tm = sel_y + (y - mv_y);
    painter.drawPixmap(x_tm,y_tm,tmp);
    painter.setPen(QPen(Qt::blue, 1, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(x_tm,y_tm,sel_w,sel_h);

    x = ui->label->x;
    y = ui->label->y;
    damj();
}

void Dialog::drawFill()
{
    QColor switchColor = Qt::darkGreen;
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

void Dialog::fillRecurs(int x, int y, QRgb switchColor, QRgb oldColor, QImage &tempImage)
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
bool Dialog::tstCus()
{
    int     lb_x = ui->label->x,
            lb_y = ui->label->y;

    if (lb_x > sel_x && lb_x < sel_x + sel_w && lb_y > sel_y && lb_y < sel_y + sel_h)
        {
            return true;
        }else{
            return false;
        }
}
void Dialog::tstRec(int x1, int y1, int x2, int y2)
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
void Dialog::on_pushButton_clicked()
{
    pix = QPixmap(ui->label->width(),ui->label->height());
    pix.fill(colr);//(Qt::white);//
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
}
void Dialog::on_pushButton_2_clicked()
{
    pix.save("C:/Users/youssef/Desktop/untitled/gg.png");
    clearpix();
}
void Dialog::on_label_mouse_Press()
{
    ui->label_3->setText("Press");
    prss = true;
    x = ui->label->x;
    y = ui->label->y;
}
void Dialog::on_label_mouse_Move()
{
    ui->label_3->setText("Move");
    ui->label_2->setText(QString("x : %1 , y : %2")
                         .arg(ui->label->x)
                         .arg(ui->label->y));
    if (prss){
        if(bt_pres == "mB_pen"){
            drawPen();
        }else if(bt_pres == "mB_sel"){
            if (sel_B){
                sel_B = false;

                if (tstCus()){
                    mv_x = x;
                    mv_y = y;
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
void Dialog::on_label_mouse_Release()
{
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
            QPainter painter(&pix);
            painter.setCompositionMode (QPainter::CompositionMode_Source);
            painter.fillRect(sel_x,sel_y,sel_w,sel_h,colr);
            painter.setCompositionMode (QPainter::CompositionMode_SourceOver);
        }
    }
    sel_M = false;

    if (bt_pres == "mB_fill"){
        drawFill();
    }

    on_pushButton_5_clicked();
}
void Dialog::on_label_mouse_leave()
{
    ui->label_3->setText("leave");
    prss = false;
}
void Dialog::on_mB_toggled(bool)
{
    QToolButton* mB = dynamic_cast<QToolButton*>(sender());
    if (bt_pres == "mB_sel"){
        QPainter painter(&pix);
        painter.drawPixmap(x_tm,y_tm,tmp);
        pixsel.fill(Qt::transparent);
        mv_x = 0;mv_y = 0;
        sel_M = false;sel_B = false;
    }
    bt_pres = mB->objectName();
    ui->label_3->setText(bt_pres);
    damj();
}
void Dialog::on_pushButton_4_clicked()
{
    pixsel.fill(Qt::transparent);
    mv_x = 0;mv_y = 0;
    sel_M = false;sel_B = false;
    tmp.fill(Qt::transparent);
    damj();
}
void Dialog::on_pushButton_5_clicked()
{
    QCryptographicHash* hash;
    QByteArray bArray;
    QBuffer buffer( &bArray );
    buffer.open( QIODevice::WriteOnly );
    pix.save( &buffer, "PNG",0 );
    //pix.loadFromData(bArray,"PNG");
    QByteArray by2 = qCompress(bArray,9); //qUncompress(by); //
    QByteArray result = hash->hash(bArray,QCryptographicHash::Md5);
    ui->label_5->setText(QString::number(bArray.size())+"  :  "+QString::number(by2.size()));

    ui->label_6->setText(result.toHex());
}
