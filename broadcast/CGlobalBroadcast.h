#pragma once

#include "CGlobalBroadcastImpl.h"

#include "../broadcastevent.h"

class CGlobalBroadcast : public CGlobalBroadcastImpl<CGlobalBroadcast, BroadcastEvent> {
	Q_OBJECT

public:
	CGlobalBroadcast(QObject* parent) : CGlobalBroadcastImpl(parent) {
		installFuncVoid();
		installFuncVariant();
		installFuncVariantList();
	}
	
private:
	void installFuncVoid() override;
	void installFuncVariant() override;
	void installFuncVariantList() override;

signals:
    //function void
    F_VOID(custom_event_void);

    //function variant
    F_VARIANT(custom_event_variant);

    //function variant list
    F_VARIANT_LIST(custom_event_variant_list);
};
