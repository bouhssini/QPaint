#include "my_qlabel.h"

my_qlabel::my_qlabel(QWidget *parent) : QLabel(parent)
{

}

void my_qlabel::mousePressEvent(QMouseEvent *event)
{
    x = event->x();
    y = event->y();
    emit mouse_Press();
}

void my_qlabel::mouseMoveEvent(QMouseEvent *event)
{
    x = event->x();
    y = event->y();
    if (x > this->width()-1) x = this->width()-1;
    if (x < 0) x = 0;
    if (y > this->height()-1) y = this->height()-1;
    if (y < 0) y = 0;

    emit mouse_Move();
}

void my_qlabel::mouseReleaseEvent(QMouseEvent *event)
{
    x = event->x();
    y = event->y();
    emit mouse_Release();
}


void my_qlabel::leaveEvent(QEvent *event)
{
    emit mouse_leave();
}

void my_qlabel::keyPressEvent(QKeyEvent *e)
{
    emit key_Press(e);
}

void my_qlabel::keyReleaseEvent(QKeyEvent *e)
{
    emit key_Release(e);
}
