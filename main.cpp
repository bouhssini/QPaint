#include "dialog.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
   QApplication::setStyle("WindowsVista");
   QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif
    Dialog w;
    w.show();

    return a.exec();
}

