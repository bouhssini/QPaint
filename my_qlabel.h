#ifndef MY_QLABEL_H
#define MY_QLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QEvent>

class my_qlabel : public QLabel
{
    Q_OBJECT
public:
    explicit my_qlabel(QWidget *parent = 0);
    int x,y;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

signals:
    void mouse_Press();
    void mouse_Move();
    void mouse_Release();
    void mouse_leave();

    void key_Release(QKeyEvent*e);
    void key_Press(QKeyEvent*e);

public slots:

};

#endif // MY_QLABEL_H
