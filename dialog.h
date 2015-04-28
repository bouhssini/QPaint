#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "nightcharts.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
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
    void clearpix();
    void drawPen();
    void drawSel();
    void drawCls();
    void drawMv();
    void drawFill();
    void fillRecurs(int x, int y, QRgb switchColor, QRgb oldColor, QImage &tempImage);
    bool tstCus();
    void tstRec(int x1,int y1,int x2,int y2);

private:
    Ui::Dialog *ui;
    QPixmap pix,pixsel,tmp;
    int x,y;
    int sel_x,sel_y,sel_w,sel_h;
    int mv_x,mv_y,x_tm,y_tm;
    bool prss,sel_B,sel_M,sel_S;
    QString bt_pres;
    QColor colr;

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_label_mouse_Press();
    void on_label_mouse_Move();
    void on_label_mouse_Release();
    void on_label_mouse_leave();
    void on_mB_toggled(bool);

    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
};

#endif // DIALOG_H
