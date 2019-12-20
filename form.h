#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QtGui>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
private:
    int tsthash(QPixmap pixtmp, int pos);
    void damj();
    void damj2(QPixmap tmp);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Form *ui;
    QPixmap pix;
};

#endif // FORM_H
