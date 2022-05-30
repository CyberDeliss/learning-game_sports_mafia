#include "day.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Day w;
    w.display();
    return a.exec();

}
