#include "aeten/lang.h"

#undef aeten_lang__interface
#define aeten_lang__interface(iface, ...) iface
#undef aeten_lang__implementation
#define aeten_lang__implementation(impl, iface) iface
#if defined(AETEN_LANG_INTERFACE)// && (!defined(AETEN_LANG_IMPLEMENTATION_H) || AETEN_LANG_IMPLEMENTATION_H == AETEN_LANG_INTERFACE)
#	define _AETEN_LANG_IFACE(prefix, suffix) _AETEN_LANG_IFACE_1(prefix, AETEN_LANG_INTERFACE, suffix)
#	define _AETEN_LANG_IFACE_1(prefix, iface, suffix) _AETEN_LANG_IFACE_2(prefix, iface, suffix)
#	define _AETEN_LANG_IFACE_2(prefix, iface, suffix) prefix##iface##suffix

#	undef aeten_lang__interface
#	define aeten_lang__interface(iface, ...) \
		_aeten_lang__define_type(iface, ##__VA_ARGS__)
AETEN_LANG_INTERFACE

#	undef aeten_lang__interface
#	define aeten_lang__interface(iface, ...) iface

#	ifdef AETEN_LANG_METHODS
/* {{{ Method definition */
#	define aeten_lang__method(type, nm, ...) \
		typedef type (*_AETEN_LANG_IFACE(_, __##nm##_t))(AETEN_LANG_INTERFACE*, ##__VA_ARGS__); \
		aeten_lang__static_constructor(_AETEN_LANG_IFACE(_, __##nm##_constr)) { \
			char *types[] = AETEN_STRING_OF_EACH(type, ##__VA_ARGS__); \
			size_t sizes[] = AETEN_SIZE_OF_EACH(type, ##__VA_ARGS__); \
			_aeten_lang__method_construct(&_AETEN_LANG_IFACE(_, _i), #nm,  types, sizes); \
		}
	AETEN_LANG_METHODS
#	undef aeten_lang__method
/* }}} */

/* {{{ Method structure */
	typedef struct _AETEN_LANG_IFACE(_, _st) {
		_aeten_lang__object_header;
#		define aeten_lang__method(type, name, ...) type (*name)(AETEN_LANG_INTERFACE*, ##__VA_ARGS__);
		AETEN_LANG_METHODS
#		undef aeten_lang__method
	} _AETEN_LANG_IFACE(_, _t);
/* }}} */

#	endif// Methods

#define _aeten_lang__message(...) _aeten_lang__message_1(__VA_ARGS__)
#define _aeten_lang__message_1(...) _aeten_lang__message_2(message #__VA_ARGS__)
#define _aeten_lang__message_2(msg) _Pragma(#msg)
#ifndef AETEN_LANG_IMPLEMENTATION_H
	#undef AETEN_LANG_METHODS
	#undef AETEN_LANG_INTERFACE
#else

#undef aeten_lang__interface
#define aeten_lang__interface(iface, ...) iface
#define aeten_lang__implementation(impl, iface) iface
#if defined(AETEN_LANG_IMPLEMENTATION_H) && (AETEN_LANG_IMPLEMENTATION_H != AETEN_LANG_INTERFACE)
	#undef AETEN_LANG_METHODS
	#undef AETEN_LANG_INTERFACE
#endif
#undef aeten_lang__implementation
#endif

#undef aeten_lang__method
#undef aeten_lang__interface

#endif
