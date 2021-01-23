#include <QCoreApplication>
#include "broadcast/testbd.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestBd testbd;
    testbd.sendEvent();

    return a.exec();
}
