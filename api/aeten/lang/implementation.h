#include "aeten/lang.h"

#ifndef _AETEN_LANG_IMPLEMENTATION_H
	#define _AETEN_LANG_IMPLEMENTATION_H
	#define _aeten_lang__private_1(prvt) prvt;
	#define _AETEN_REF_OF_EACH_IFACE(iface) &_##iface##_i,
#endif


#ifdef AETEN_LANG_IMPLEMENTATION_H
	#define _AETEN_LANG_IMPL(prefix, suffix) _AETEN_LANG_IMPL_1(prefix, AETEN_LANG_IMPLEMENTATION_H, suffix)
	#define _AETEN_LANG_IMPL_1(prefix, impl, suffix) _AETEN_LANG_IMPL_2(prefix, impl, suffix)
	#define _AETEN_LANG_IMPL_2(prefix, impl, suffix) prefix##impl##suffix

	#define aeten_lang__method(type, name, ...) type (*name)(AETEN_LANG_INTERFACE*, ##__VA_ARGS__);
	#define aeten_lang__private(...) AETEN_FOR_EACH(_aeten_lang__private_1, ##__VA_ARGS__)
	#define aeten_lang__interface(iface, ...) iface
	#define aeten_lang__implementation(impl, iface) impl

	//typedef struct _##impl##_ms {} _##impl##_m;
	typedef struct _AETEN_LANG_IMPL(_, _ms) {} _AETEN_LANG_IMPL(_, _m);

	//static _##impl##_m _##impl##_methods;
	static _AETEN_LANG_IMPL(_, _m) _AETEN_LANG_IMPL(_, _methods);
	#undef  aeten_lang__implementation
	#define aeten_lang__implementation(impl, iface) impl, iface

	//_aeten_lang__define_type(impl, iface)
	#define _aeten_lang__define_type_1(impl) _aeten_lang__define_type(impl)
	_aeten_lang__define_type_1(AETEN_LANG_IMPLEMENTATION_H)
	#undef  _aeten_lang__define_type_1

	//typedef struct _##impl##__private_st { [...] } _##impl##__private_t;
	#undef  aeten_lang__implementation
	#define aeten_lang__implementation(impl, ...) impl
	typedef struct _AETEN_LANG_IMPL(_, __private_st) {
		AETEN_LANG_PRIVATE
	} _AETEN_LANG_IMPL(_, __private_t);

	//typedef struct _##impl##_st { header + methods } _##impl##_t;
	typedef struct _AETEN_LANG_IMPL(_, _st) {
		_aeten_lang__object_header;
		AETEN_LANG_METHODS
		_AETEN_LANG_IMPL(_, __private_t) _private;
	} AETEN_LANG_IMPLEMENTATION_H;

	//type impl##__##mthd)(iface*, ##__VA_ARGS__)
	#undef  aeten_lang__method
	#define aeten_lang__method(type, mthd, ...) \
		type _AETEN_LANG_IMPL(, __##mthd)(AETEN_LANG_INTERFACE* instance, ##__VA_ARGS__)
	AETEN_LANG_METHODS

	//iface* impl##__initialize(__VA_ARGS__)
	#define aeten_lang__constructor(...) \
		AETEN_LANG_INTERFACE* _AETEN_LANG_IMPL(, __initialize)(AETEN_LANG_IMPLEMENTATION_H* instance, __VA_ARGS__);
	AETEN_LANG_CONSTRUCTORS

	//iface* impl##__new(__VA_ARGS__)
	#undef  aeten_lang__constructor
	#ifdef AETEN_LANG_IMPLEMENTATION_C
		#define _aeten_lang__arg_1(i, x) x x##_##i
		#define _aeten_lang__arg_2(i, x) x##_##i
		#define _aeten_lang__arg_3(...) _aeten_lang__arg_4(__VA_ARGS__)
		#define _aeten_lang__arg_4(...) __VA_ARGS__
		#define aeten_lang__constructor(...) \
			AETEN_LANG_INTERFACE* _AETEN_LANG_IMPL(, __new)(_aeten_lang__arg_3(AETEN_FOR_EACH_I(_aeten_lang__arg_1, ##__VA_ARGS__))) { \
			AETEN_LANG_IMPLEMENTATION_H *instance = (AETEN_LANG_IMPLEMENTATION_H *) calloc(1, sizeof(AETEN_LANG_IMPLEMENTATION_H)); \
			_AETEN_LANG_IMPL(, __initialize)(instance, AETEN_FOR_EACH_I(_aeten_lang__arg_2, ##__VA_ARGS__)); \
			return aeten_lang__cast_ref(AETEN_LANG_INTERFACE, instance); \
		}
	#else
		#define aeten_lang__constructor(...) \
			AETEN_LANG_INTERFACE* _AETEN_LANG_IMPL(, __new)(__VA_ARGS__);
	#endif
	AETEN_LANG_CONSTRUCTORS

	//void impl##__finalize(impl*)
	void _AETEN_LANG_IMPL(, __finalize)(AETEN_LANG_IMPLEMENTATION_H* instance);

	/*	{{{ Instance init */
	//void impl##__init(impl*)
	void _AETEN_LANG_IMPL(_, __init) (AETEN_LANG_IMPLEMENTATION_H * instance)
	#ifdef AETEN_LANG_IMPLEMENTATION_C
	{
		memset(instance, 0, sizeof(AETEN_LANG_IMPLEMENTATION_H));
		instance->_interface = &_AETEN_LANG_IMPL(_, _i);
		instance->_initialize = (aeten_lang__initializer_t)_AETEN_LANG_IMPL(, __initialize);
		instance->_finalize = (aeten_lang__finalizer_t)_AETEN_LANG_IMPL(, __finalize);
		/* methods */
		#undef  aeten_lang__method
		#define aeten_lang__method(type, mthd, ...) \
			instance->mthd = _AETEN_LANG_IMPL(, __##mthd);
		AETEN_LANG_METHODS
	}
	#else
	;
	#endif
/*	}}} */


	#undef aeten_lang__implementation
	#undef aeten_lang__constructor
	#undef aeten_lang__private
	#undef aeten_lang__method
	#undef _AETEN_LANG_IMPL
	#undef _AETEN_LANG_IMPL_1
	#undef _AETEN_LANG_IMPL_2
	#undef AETEN_LANG_METHODS
	#undef AETEN_LANG_INTERFACE
	#undef AETEN_LANG_IMPLEMENTATION_H

#endif
