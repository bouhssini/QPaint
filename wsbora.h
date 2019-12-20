#ifndef WSBORA_H
#define WSBORA_H

#include <QWidget>
#include "nightcharts.h"

namespace Ui {
class wSbora;
}

class wSbora : public QWidget
{
    Q_OBJECT

public:
    explicit wSbora(QWidget *parent = 0);
    ~wSbora();
    inline int tstVal(int x,int y,bool b)
    {
        if (b){
            if (x > y) return x;
            else return y;
        }else{
            if (x < y) return x;
            else return y;
        }

    }
    void damj();
    void damjview(QByteArray bArray);
    void clearpix();
    void drawPen();
    void drawLine();
    void drawSel();
    void drawCls();
    void drawMv();
    void drawpip();
    void drawFill();
    void fillRecurs(int x, int y, QRgb switchColor, QRgb oldColor, QImage &tempImage);
    bool tstCus();
    void tstRec(int x1,int y1,int x2,int y2);
    void SetColorChoix(QColor co);
    QColor ColorChoix();
    void DeleteSel();
    void CancelSel();
    void MByan();

private:
    Ui::wSbora *ui;
    QPixmap pix,pixsel,tmp;
    int x,y;
    int sel_x,sel_y,sel_w,sel_h;
    int mv_x,mv_y,x_tm,y_tm;
    bool prss,sel_B,sel_M,sel_S;
    QString bt_pres;
    QColor colorBackground;
    QColor colorChoix;
    QPixmap PicBackground;
    QString imgType;
    int PenSize;
    bool Dcopy;

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_mB_toggled(bool);

    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

    void on_label_mouse_Press();
    void on_label_mouse_Move();
    void on_label_mouse_Release();
    void on_label_mouse_leave();
    void on_label_key_Press(QKeyEvent *e);
    void on_label_key_Release(QKeyEvent *e);

    void on_lacolor_mouse_Press();
    void on_spinBox_valueChanged(int arg1);

    void on_mB_mbyan_clicked();
};

#endif // WSBORA_H
