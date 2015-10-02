#include "aeten/lang.h"

#ifndef _AETEN_LANG_IMPLEMENTATION_H
#	define _AETEN_LANG_IMPLEMENTATION_H

#	define _aeten_lang__implementation_1(impl, ...) _aeten_lang__implementation_1_1(impl, ##__VA_ARGS__)
#	define _aeten_lang__implementation_1_1(impl, ...) \
		typedef struct _##impl##_ms {} _##impl##_m; \
		static _##impl##_m _##impl##_methods; \
		_aeten_lang__define_type(impl, ##__VA_ARGS__) \
		typedef struct _##impl##__private_st {
			// private
#	define _aeten_lang__implementation_2(impl, ...) _aeten_lang__implementation_2_1(impl, ##__VA_ARGS__)
#	define _aeten_lang__implementation_2_1(impl) \
		} _##impl##__private_t; \
		typedef struct _##impl##_st { \
			aeten_lang__object_header;
			// methods
#	define _aeten_lang__implementation_3(impl, ...) _aeten_lang__implementation_3_1(impl, ##__VA_ARGS__)
#	define _aeten_lang__implementation_3_1(impl) \
			_##impl##__private_t _private; \
		} impl;

#	define _aeten_lang__private_1(prvt) prvt;
#	define _AETEN_REF_OF_EACH_IFACE(iface) &_##iface##_i,
#endif

#ifdef AETEN_LANG_IMPLEMENTATION_H

#	define aeten_lang__interface(iface, ...) iface
#	define aeten_lang__method(type, name, ...) type (*name)(AETEN_LANG_INTERFACE*, ##__VA_ARGS__);
#	undef aeten_lang__private
#	define aeten_lang__private(...)
#	undef aeten_lang__constructor
#	define aeten_lang__constructor(...)
#	define aeten_lang__implementation(impl, ...) impl, ##__VA_ARGS__
	_aeten_lang__implementation_1(AETEN_LANG_IMPLEMENTATION_H)
#	undef aeten_lang__implementation
#	define aeten_lang__implementation(...)
#	undef aeten_lang__private
#	define aeten_lang__private(...) AETEN_FOR_EACH(_aeten_lang__private_1, ##__VA_ARGS__)
	AETEN_LANG_IMPLEMENTATION_H
#	undef aeten_lang__private
#	define aeten_lang__private(...)
#	undef aeten_lang__implementation
#	define aeten_lang__implementation(impl, ...) impl
	_aeten_lang__implementation_2(AETEN_LANG_IMPLEMENTATION_H)
	AETEN_LANG_METHODS
#	undef aeten_lang__method
#	define aeten_lang__method(...)
	_aeten_lang__implementation_3(AETEN_LANG_IMPLEMENTATION_H)

#	define _AETEN_LANG_IMPL(prefix, suffix) _AETEN_LANG_IMPL_1(prefix, AETEN_LANG_IMPLEMENTATION_H, suffix)
#	define _AETEN_LANG_IMPL_1(prefix, implem, suffix) _AETEN_LANG_IMPL_2(prefix, implem, suffix)
#	define _AETEN_LANG_IMPL_2(prefix, implem, suffix) prefix##implem##_##suffix

#	undef aeten_lang__method
#	define aeten_lang__method(type, name, ...) \
		type _AETEN_LANG_IMPL(, _##name)(AETEN_LANG_INTERFACE*, ##__VA_ARGS__)
	AETEN_LANG_METHODS
#	undef aeten_lang__method


	AETEN_LANG_IMPLEMENTATION_H* _AETEN_LANG_IMPL(, _initialize)(
		AETEN_LANG_IMPLEMENTATION_H*,
#		undef aeten_lang__implementation
#		define aeten_lang__implementation(...)
#		undef aeten_lang__constructor
#		define aeten_lang__constructor(...) __VA_ARGS__
		AETEN_LANG_IMPLEMENTATION_H
#		undef aeten_lang__constructor
#		define aeten_lang__constructor(...)
	);
#	undef aeten_lang__implementation
#	define aeten_lang__implementation(impl, ...) impl
	AETEN_LANG_IMPLEMENTATION_H* _AETEN_LANG_IMPL(, _new)(
#		undef aeten_lang__implementation
#		define aeten_lang__implementation(...)
#		undef aeten_lang__constructor
#		define aeten_lang__constructor(...) __VA_ARGS__
		AETEN_LANG_IMPLEMENTATION_H
#		undef aeten_lang__constructor
#		define aeten_lang__constructor(...)
	);
#	undef aeten_lang__implementation
#	define aeten_lang__implementation(impl, ...) impl
	void _AETEN_LANG_IMPL(, _finalize)();

	/*	{{{ Instance init */
	void _AETEN_LANG_IMPL(_, _init) (AETEN_LANG_IMPLEMENTATION_H *instance)
#ifdef AETEN_LANG_IMPLEMENTATION_C
	{
		memset(instance, 0, sizeof(AETEN_LANG_IMPLEMENTATION_H));
		instance->interface = &_AETEN_LANG_IMPL(_, i);
		instance->initialize = (aeten_lang__initializer_t)_AETEN_LANG_IMPL(, _initialize);
		instance->finalize = (aeten_lang__finalizer_t)_AETEN_LANG_IMPL(, _finalize);
		/* methods */
#		undef aeten_lang__implementation
#		define aeten_lang__implementation(impl, ...) __VA_ARGS__
#		define IFACES(iface) IFACES_1(iface)
#		define IFACES_1(iface) IFACES_2(iface)
#		define IFACES_2(iface) iface
#		define aeten_lang__method(type, method, ...) \
			instance->method = _AETEN_LANG_IMPL(, _##method) \
		AETEN_LANG_METHODS
#		undef aeten_lang__method
#		undef aeten_lang__implementation
#		define aeten_lang__implementation(impl, ...) impl
#		define _AETEN_LANG_IMPL(prefix, suffix) _AETEN_LANG_IMPL_1(prefix, AETEN_LANG_IMPLEMENTATION_H, suffix)
#		define _AETEN_LANG_IMPL_1(prefix, implem, suffix) _AETEN_LANG_IMPL_2(prefix, implem, suffix)
#		define _AETEN_LANG_IMPL_2(prefix, implem, suffix) prefix##implem##_##suffix
#		define aeten_lang__method(type, mthd, ...) \
			instance->mthd = _AETEN_LANG_IMPL(, _##mthd)
		AETEN_LANG_METHODS
#		undef aeten_lang__method
	}
#else
	;
#endif
/*	}}} */


#	undef aeten_lang__implementation
#	undef aeten_lang__constructor
#	undef aeten_lang__private
#	undef _AETEN_LANG_IMPL
#	undef _AETEN_LANG_IMPL_1
#	undef _AETEN_LANG_IMPL_2
#	undef aeten_lang__method
#	undef AETEN_LANG_METHODS
#	undef AETEN_LANG_INTERFACE
#	undef AETEN_LANG_IMPLEMENTATION_H

#endif
