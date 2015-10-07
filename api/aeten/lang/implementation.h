#include "aeten/lang.h"

#ifdef AETEN_LANG_IMPLEMENTATION_H
	#define _AETEN_LANG_IMPL(prefix, suffix) _AETEN_LANG_IMPL_1(prefix, AETEN_LANG_IMPLEMENTATION_H, suffix)
	#define _AETEN_LANG_IMPL_1(prefix, impl, suffix) _AETEN_LANG_IMPL_2(prefix, impl, suffix)
	#define _AETEN_LANG_IMPL_2(prefix, impl, suffix) prefix##impl##suffix

	#define _aeten_lang__private_1(prvt) prvt;
	#define aeten_lang__method(type, name, ...) type (*name)(AETEN_LANG_INTERFACE*, ##__VA_ARGS__);
	#define aeten_lang__private(...) AETEN_FOR_EACH(_aeten_lang__private_1, ##__VA_ARGS__)
	#define aeten_lang__interface(iface, ...) iface
	#undef aeten_lang__implementation
	#define aeten_lang__implementation(impl, iface) impl

	//typedef struct _##impl##_ms {} _##impl##_m;
	typedef struct _AETEN_LANG_IMPL(_, _ms) {} _AETEN_LANG_IMPL(_, _m);

	//_aeten_lang__define_type(impl, iface)
	#undef  aeten_lang__implementation
	#define aeten_lang__implementation(impl, iface) impl, iface
	#define _aeten_lang__define_type_1(impl) \
		_aeten_lang__define_type(impl)
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
		AETEN_LANG_INTERFACE* _AETEN_LANG_IMPL(, __initialize)(AETEN_LANG_IMPLEMENTATION_H* instance, ##__VA_ARGS__);
	AETEN_LANG_CONSTRUCTORS

	#define _aeten_lang__arg_1(i, x) x arg_##i
	#define _aeten_lang__arg_2(i, x) arg_##i
	#define _aeten_lang__arg_3(...) _aeten_lang__arg_4(__VA_ARGS__)
	#define _aeten_lang__arg_4(...) __VA_ARGS__


	//void impl##__finalize(impl*)
	void _AETEN_LANG_IMPL(, __finalize)(AETEN_LANG_IMPLEMENTATION_H* instance);

	/*	{{{ Instance init */
	//void impl##__init(impl*)
#undef  aeten_lang__constructor
	void _AETEN_LANG_IMPL(_, __init_interface) (AETEN_LANG_IMPLEMENTATION_H* instance);
#if (AETEN_LANG_IMPLEMENTATION_H == AETEN_LANG_INTERFACE)
	#ifdef AETEN_LANG_IMPLEMENTATION_C
		#undef  aeten_lang__method
		#define aeten_lang__method(type, mthd, ...) \
			instance->mthd = _AETEN_LANG_IMPL(, __##mthd);
		void _AETEN_LANG_IMPL(_, __init_interface) (AETEN_LANG_IMPLEMENTATION_H* instance) {
			memset(instance, 0, sizeof(AETEN_LANG_IMPLEMENTATION_H));
			/* methods */
			AETEN_LANG_METHODS
			instance->_interface = AETEN_STRINGIZE(AETEN_LANG_IMPLEMENTATION_H);
			instance->_initialize = (aeten_lang__initializer_t)_AETEN_LANG_IMPL(, __initialize);
			instance->_finalize = (aeten_lang__finalizer_t)_AETEN_LANG_IMPL(, __finalize);
		}
#endif

#if (AETEN_LANG_IMPLEMENTATION_H == AETEN_LANG_INTERFACE)
	#define aeten_lang__constructor(...) \
		AETEN_LANG_INTERFACE* _AETEN_LANG_IMPL(_, __init)(AETEN_LANG_IMPLEMENTATION_H* instance, _aeten_lang__arg_3(AETEN_FOR_EACH_I(_aeten_lang__arg_1, ##__VA_ARGS__)));
	AETEN_LANG_CONSTRUCTORS
	#ifdef AETEN_LANG_IMPLEMENTATION_C
		#undef  aeten_lang__constructor
		#define aeten_lang__constructor(...) \
			AETEN_LANG_INTERFACE* _AETEN_LANG_IMPL(_, __init)(AETEN_LANG_IMPLEMENTATION_H* instance, _aeten_lang__arg_3(AETEN_FOR_EACH_I(_aeten_lang__arg_1, ##__VA_ARGS__))) { \
				memset(instance, 0, sizeof(AETEN_LANG_IMPLEMENTATION_H)); \
				_AETEN_LANG_IMPL(_, __init_interface)(instance); \
				_AETEN_LANG_IMPL(, __initialize)(instance, AETEN_FOR_EACH_I(_aeten_lang__arg_2, ##__VA_ARGS__)); \
				return (AETEN_LANG_INTERFACE*)instance; \
			}
		AETEN_LANG_CONSTRUCTORS
	#endif
#endif

	//iface* impl##__new(__VA_ARGS__)
	#undef  aeten_lang__constructor
	#ifdef AETEN_LANG_IMPLEMENTATION_C
		#define aeten_lang__constructor(...) \
			AETEN_LANG_INTERFACE* _AETEN_LANG_IMPL(, __new)(_aeten_lang__arg_3(AETEN_FOR_EACH_I(_aeten_lang__arg_1, ##__VA_ARGS__))); \
			AETEN_LANG_INTERFACE* _AETEN_LANG_IMPL(, __new)(_aeten_lang__arg_3(AETEN_FOR_EACH_I(_aeten_lang__arg_1, ##__VA_ARGS__))) { \
			AETEN_LANG_IMPLEMENTATION_H *instance = (AETEN_LANG_IMPLEMENTATION_H *) calloc(1, sizeof(AETEN_LANG_IMPLEMENTATION_H)); \
			_AETEN_LANG_IMPL(_, __init)(instance, AETEN_FOR_EACH_I(_aeten_lang__arg_2, ##__VA_ARGS__)); \
			return aeten_lang__cast_ref(AETEN_LANG_INTERFACE, instance); \
		}
	#else
		#define aeten_lang__constructor(...) \
			AETEN_LANG_INTERFACE* _AETEN_LANG_IMPL(, __new)(_aeten_lang__arg_3(AETEN_FOR_EACH_I(_aeten_lang__arg_1, ##__VA_ARGS__)));
	#endif
	AETEN_LANG_CONSTRUCTORS
#endif
/*	}}} */


#undef _aeten_lang__private_1
#undef aeten_lang__implementation
#undef aeten_lang__constructor
#undef aeten_lang__private
#undef aeten_lang__method
#undef _AETEN_LANG_IMPL
#undef _AETEN_LANG_IMPL_1
#undef _AETEN_LANG_IMPL_2
#undef AETEN_LANG_IMPLEMENTATION_H
#undef AETEN_LANG_PRIVATE
#undef AETEN_LANG_CONSTRUCTORS
#undef AETEN_LANG_IMPLEMENTATION_C
#undef AETEN_LANG_METHODS
#undef AETEN_LANG_INTERFACE
#endif
