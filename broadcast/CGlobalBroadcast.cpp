#include "CGlobalBroadcast.h"

#ifdef __GNUC__
template<>
CGlobalBroadcast* CGlobalBroadcastImpl<CGlobalBroadcast,BroadcastEvent>::globalBroadcast = nullptr;
#else
CGlobalBroadcast* CGlobalBroadcast::globalBroadcast = nullptr;
#endif

void CGlobalBroadcast::installFuncVoid() {
    funcMap_void.insert(BroadcastEvent::CUSTOM_EVENT_VOID, &CGlobalBroadcast::custom_event_void);

}

void CGlobalBroadcast::installFuncVariant() {
    funcMap_variant.insert(BroadcastEvent::CUSTOM_EVENT_VARIANT, &CGlobalBroadcast::custom_event_variant);

}

void CGlobalBroadcast::installFuncVariantList() {
    funcMap_variant_list.insert(BroadcastEvent::CUSTOM_EVENT_VARIANT_LIST, &CGlobalBroadcast::custom_event_variant_list);

}
