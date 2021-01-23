#pragma once

#include <qobject.h>
#include <qvariant.h>
#include <qhash.h> 

template<typename T, typename B>
class CGlobalBroadcastImpl : public QObject {
public:
	CGlobalBroadcastImpl<T, B>(QObject* parent) : QObject(parent) {}

public:
	static void Install(QObject* parent) {
		if (globalBroadcast == nullptr) {
			globalBroadcast = new T(parent);
		}
	}

	template<typename F>
	static void RegisterEvent(typename B::Event_Void id, F f);

	template<typename F>
	static void RegisterEvent(typename B::Event_Variant id, F f);

	template<typename F>
	static void RegisterEvent(typename B::Event_Variant_List id, F f);

	//connect auto
	template<typename F>
	static void RegisterEvent(typename B::Event_Void id, const QObject* context, F f);

	template<typename F>
	static void RegisterEvent(typename B::Event_Variant id, const QObject* context, F f);

	template<typename F>
	static void RegisterEvent(typename B::Event_Variant_List id, const QObject* context, F f);

	static void PostEvent(typename B::Event_Void id) {
		emit (globalBroadcast->*(globalBroadcast->funcMap_void.value(id)))();
	}

	static void PostEvent(typename B::Event_Variant id, QVariant data) {
		emit (globalBroadcast->*(globalBroadcast->funcMap_variant.value(id)))(data);
	}

	static void PostEvent(typename B::Event_Variant_List id, QVariantList data) {
		emit (globalBroadcast->*(globalBroadcast->funcMap_variant_list.value(id)))(data);
	}

private:
	typedef void (T::*func_void)();
	typedef void (T::*func_variant)(QVariant);
	typedef void (T::*func_variant_list)(QVariantList);

protected:
	static T* globalBroadcast;
	//function map
	QHash<typename B::Event_Void, func_void> funcMap_void;
	QHash<typename B::Event_Variant, func_variant> funcMap_variant;
	QHash<typename B::Event_Variant_List, func_variant_list> funcMap_variant_list;

private:
	virtual void installFuncVoid() = 0;
	virtual void installFuncVariant() = 0;
	virtual void installFuncVariantList() = 0;

#define F_VOID(f_n)			void f_n()
#define F_VARIANT(f_n)		void f_n(QVariant data)
#define F_VARIANT_LIST(f_n)	void f_n(QVariantList data)
};

template<typename T, typename B>
template<typename F>
inline void CGlobalBroadcastImpl<T, B>::RegisterEvent(typename B::Event_Void id, F f)
{
	connect(globalBroadcast, globalBroadcast->funcMap_void.value(id), f);
}

template<typename T, typename B>
template<typename F>
inline void CGlobalBroadcastImpl<T, B>::RegisterEvent(typename B::Event_Variant id, F f)
{
	connect(globalBroadcast, globalBroadcast->funcMap_variant.value(id), f);
}

template<typename T, typename B>
template<typename F>
inline void CGlobalBroadcastImpl<T, B>::RegisterEvent(typename B::Event_Variant_List id, F f) {
	connect(globalBroadcast, globalBroadcast->funcMap_variant_list.value(id), f);
}

template<typename T, typename B>
template<typename F>
inline void CGlobalBroadcastImpl<T, B>::RegisterEvent(typename B::Event_Void id, const QObject * context, F f)
{
	connect(globalBroadcast, globalBroadcast->funcMap_void.value(id), context, f);
}

template<typename T, typename B>
template<typename F>
inline void CGlobalBroadcastImpl<T, B>::RegisterEvent(typename B::Event_Variant id, const QObject * context, F f)
{
	connect(globalBroadcast, globalBroadcast->funcMap_variant.value(id), context, f);
}

template<typename T, typename B>
template<typename F>
inline void CGlobalBroadcastImpl<T, B>::RegisterEvent(typename B::Event_Variant_List id, const QObject * context, F f)
{
	connect(globalBroadcast, globalBroadcast->funcMap_variant_list.value(id), context, f);
}

