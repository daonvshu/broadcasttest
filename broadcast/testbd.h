#ifndef TESTBD_H
#define TESTBD_H

#include "CGlobalBroadcast.h"

struct StructA {
    int a;
    QString b;
};
Q_DECLARE_METATYPE(StructA);

class TestBd : public QObject
{
public:
    TestBd(QObject* parent = nullptr);
    void sendEvent();
};

#endif // TESTBD_H
