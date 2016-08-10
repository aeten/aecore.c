
#include "aeten/lang.h"

#ifdef AETEN_LANG_IMPLEMENTATION_H
	#define AETEN_LANG_IMPL(prefix, suffix) AETEN_LANG_IMPL_1(prefix, AETEN_LANG_IMPLEMENTATION_H, suffix)
	#define AETEN_LANG_IMPL_1(prefix, impl, suffix) AETEN_LANG_IMPL_2(prefix, impl, suffix)
	#define AETEN_LANG_IMPL_2(prefix, impl, suffix) prefix##impl##suffix

	#define aeten_lang__private_1(prvt) prvt;
	#define aeten_lang__method(type, name, ...) type (*name)(AETEN_LANG_INTERFACE*, ##__VA_ARGS__);
	#define aeten_lang__private(...) AETEN_FOR_EACH(aeten_lang__private_1, ##__VA_ARGS__)
	#define aeten_lang__implementation(impl, iface) impl


	#define _aeten_va_args_2(...) __VA_ARGS__
	#define _aeten_va_args_1(...) _aeten_va_args_2(instance, ##__VA_ARGS__)
	#define _aeten_va_args(...) _aeten_va_args_1(__VA_ARGS__)
	#define _aeten_arg_name_3(n) arg_ ## n
	#define _aeten_arg_name_2(n) _aeten_arg_name_3(n)
	#define _aeten_arg_name_1(...) _aeten_arg_name_2(AETEN_FOR_EACH_NARG(x, ##__VA_ARGS__))
	#define _aeten_arg_name(...) _aeten_arg_name_1(__VA_ARGS__)

	typedef struct AETEN_LANG_IMPL(, _st) AETEN_LANG_IMPLEMENTATION_H;

	struct AETEN_LANG_IMPL(_, _st) {
		aeten_lang__implementation_t _implementation;
		struct {
			AETEN_LANG_PRIVATE
		} _private;
	};

	struct AETEN_LANG_IMPL(, _st) {
		struct AETEN_LANG_IMPL(_, _st);
		#undef  aeten_lang__implementation
		#define aeten_lang__implementation(impl, iface, ...) iface, ##__VA_ARGS__
		#undef _aeten_lang__as_inherit
		#define _aeten_lang__as_inherit(iface) \
			iface* _as__##iface; \
			aeten_lang__implementation_t* _##iface##__impl; \
			struct _##iface##_st;
		AETEN_FOR_EACH(_aeten_lang__as_inherit, AETEN_LANG_IMPLEMENTATION_H)
	};


	#undef  aeten_lang__implementation
	#define aeten_lang__implementation(impl, iface, ...) impl, iface, ##__VA_ARGS__
	#define aeten_lang__define_type_1(impl) \
		_aeten_lang__define_type(impl)
	aeten_lang__define_type_1(AETEN_LANG_IMPLEMENTATION_H)

	#undef aeten_lang__interface
	#define aeten_lang__interface(iface, ...) iface
	#undef  aeten_lang__implementation
	#define aeten_lang__implementation(impl, iface) impl
	#define aeten_lang__constructor(...) \
		void AETEN_LANG_IMPL(, __initialize)(AETEN_LANG_IMPLEMENTATION_H* instance, ##__VA_ARGS__);
	AETEN_LANG_CONSTRUCTORS

	#define aeten_lang__arg_1(i, x) x arg_##i
	#define aeten_lang__arg_2(i, x) arg_##i
	#define aeten_lang__arg_3(...) aeten_lang__arg_4(__VA_ARGS__)
	#define aeten_lang__arg_4(...) __VA_ARGS__


	void AETEN_LANG_IMPL(, __finalize)(AETEN_LANG_IMPLEMENTATION_H* instance);
	void AETEN_LANG_IMPL(_, __init_interface) (void* instance);

	#undef  aeten_lang__constructor
	#ifdef AETEN_LANG_IMPLEMENTATION_C
		void AETEN_LANG_IMPL(_, __finalize_)(void* ref);
		void AETEN_LANG_IMPL(_, __finalize_)(void* ref) {
			AETEN_LANG_IMPL(, __finalize)((*((aeten_lang__implementation_t**)ref))->instance);
		}
		void AETEN_LANG_IMPL(_, __init_interface) (void* ref) {
			AETEN_LANG_IMPLEMENTATION_H* instance = (AETEN_LANG_IMPLEMENTATION_H*)ref;
			unsigned long int offset = sizeof(struct AETEN_LANG_IMPL(_, _st));
			memset(instance, 0, sizeof(AETEN_LANG_IMPLEMENTATION_H));
			instance->_implementation.interface = AETEN_STRINGIZE(AETEN_LANG_IMPLEMENTATION_H);
			instance->_implementation.instance = instance;
			instance->_implementation.size = sizeof(AETEN_LANG_IMPLEMENTATION_H);
			instance->_implementation.finalize = (aeten_lang__finalizer_t)AETEN_LANG_IMPL(_, __finalize_);
			#undef  aeten_lang__init_legacy
			#define aeten_lang__init_legacy(iface) \
				offset += sizeof(instance->_as__##iface); \
				instance->_as__##iface = (void*)(((unsigned long int) instance) + offset); \
				AETEN_LANG_IMPL(_, _##iface##__init_interface)(&instance->_implementation, &offset);
			#undef aeten_lang__interface
			#define aeten_lang__interface(iface, ...) iface //, ##__VA_ARGS__
			AETEN_FOR_EACH(aeten_lang__init_legacy, AETEN_LANG_INTERFACE)
		}
	#endif

	#undef aeten_lang__interface
	#define aeten_lang__interface(iface, ...) iface
	#define aeten_lang__constructor(...) \
		void AETEN_LANG_IMPL(_, __init)(aeten_lang__arg_3(AETEN_FOR_EACH_I(aeten_lang__arg_1, AETEN_LANG_IMPLEMENTATION_H*, ##__VA_ARGS__)));
	AETEN_LANG_CONSTRUCTORS
	#ifdef AETEN_LANG_IMPLEMENTATION_C
		#undef  aeten_lang__constructor
		#define aeten_lang__constructor(...) \
			void AETEN_LANG_IMPL(_, __init)(aeten_lang__arg_3(AETEN_FOR_EACH_I(aeten_lang__arg_1, AETEN_LANG_IMPLEMENTATION_H*, ##__VA_ARGS__))) { \
				memset(_aeten_arg_name(__VA_ARGS__), 0, sizeof(AETEN_LANG_IMPLEMENTATION_H)); \
				AETEN_LANG_IMPL(_, __init_interface)(_aeten_arg_name(__VA_ARGS__)); \
				AETEN_LANG_IMPL(, __initialize)(AETEN_FOR_EACH_I(aeten_lang__arg_2, _aeten_arg_name(__VA_ARGS__), ##__VA_ARGS__)); \
			}
		AETEN_LANG_CONSTRUCTORS
	#endif

	#define aeten_lang__constructor_cast(iface, instance) cast(iface, instance)
	#undef  aeten_lang__constructor
	#ifdef AETEN_LANG_IMPLEMENTATION_C
		#define aeten_lang__constructor(...) \
			AETEN_LANG_INTERFACE* AETEN_LANG_IMPL(, __new)(aeten_lang__arg_3(AETEN_FOR_EACH_I(aeten_lang__arg_1, ##__VA_ARGS__))); \
			AETEN_LANG_INTERFACE* AETEN_LANG_IMPL(, __new)(aeten_lang__arg_3(AETEN_FOR_EACH_I(aeten_lang__arg_1, ##__VA_ARGS__))) { \
				AETEN_LANG_IMPLEMENTATION_H *instance = (AETEN_LANG_IMPLEMENTATION_H *) calloc(1, sizeof(AETEN_LANG_IMPLEMENTATION_H)); \
				AETEN_LANG_IMPL(_, __init)(_aeten_va_args(AETEN_FOR_EACH_I(aeten_lang__arg_2, ##__VA_ARGS__))); \
				return aeten_lang__constructor_cast(AETEN_LANG_INTERFACE, instance); \
			}
	#else
		#define aeten_lang__constructor(...) \
			AETEN_LANG_INTERFACE* AETEN_LANG_IMPL(, __new)(aeten_lang__arg_3(AETEN_FOR_EACH_I(aeten_lang__arg_1, ##__VA_ARGS__)));
	#endif
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wstrict-prototypes"
	#pragma GCC diagnostic ignored "-Wold-style-definition"
	AETEN_LANG_CONSTRUCTORS
	#pragma GCC diagnostic pop
	#undef aeten_lang__constructor_cast


	#undef _aeten_va_args_2
	#undef _aeten_va_args_1
	#undef _aeten_va_args
	#undef _aeten_arg_name_3
	#undef _aeten_arg_name_2
	#undef _aeten_arg_name_1
	#undef _aeten_arg_name
	#undef aeten_lang__private
	#undef aeten_lang__private_1
	#undef aeten_lang__define_type_1
	#undef aeten_lang__implementation
	#undef aeten_lang__constructor
	#undef aeten_lang__method
	#undef aeten_lang__arg_1
	#undef aeten_lang__arg_2
	#undef aeten_lang__arg_3
	#undef aeten_lang__arg_4
	#undef AETEN_LANG_IMPL
	#undef AETEN_LANG_IMPL_1
	#undef AETEN_LANG_IMPL_2
	#undef AETEN_LANG_IMPLEMENTATION_H
	#undef AETEN_LANG_PRIVATE
	#undef AETEN_LANG_CONSTRUCTORS
	#undef AETEN_LANG_IMPLEMENTATION_C
	#undef AETEN_LANG_METHODS
	#undef AETEN_LANG_INTERFACE
#endif
