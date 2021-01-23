#include "testbd.h"
#include <QDebug>

TestBd::TestBd(QObject* parent) : QObject(parent)
{
    CGlobalBroadcast::Install(this);

    //接收没有参数的通知
    CGlobalBroadcast::RegisterEvent(BroadcastEvent::CUSTOM_EVENT_VOID, [&]() {
        //do something...
    });
    //接收A发送的QString
    CGlobalBroadcast::RegisterEvent(BroadcastEvent::CUSTOM_EVENT_VARIANT, this, [&](QVariant data) {
        qDebug() << data;
        //do something...
    });
    //接收A发送的结构体
    CGlobalBroadcast::RegisterEvent(BroadcastEvent::CUSTOM_EVENT_VARIANT, [&](QVariant data) {
        auto structA = data.value<StructA>();
        //do something...
    });
    //接收A发送的一堆数据
    CGlobalBroadcast::RegisterEvent(BroadcastEvent::CUSTOM_EVENT_VARIANT_LIST, [&](QVariantList data) {
        auto dataInt = data.at(0).toInt();
        auto dataStr = data.at(1).toString();
        //do something...
    });
}

void TestBd::sendEvent(){
    //没有参数的通知
    CGlobalBroadcast::PostEvent(BroadcastEvent::CUSTOM_EVENT_VOID);
    //发送1个QString
    CGlobalBroadcast::PostEvent(BroadcastEvent::CUSTOM_EVENT_VARIANT, "hello B!");
    //发送1个StructA
    StructA structA;
    CGlobalBroadcast::PostEvent(BroadcastEvent::CUSTOM_EVENT_VARIANT, QVariant::fromValue(structA));
    //发送一堆数据
    QVariantList data;
    data << 1;
    data << "abc";
    CGlobalBroadcast::PostEvent(BroadcastEvent::CUSTOM_EVENT_VARIANT_LIST, data);
}
