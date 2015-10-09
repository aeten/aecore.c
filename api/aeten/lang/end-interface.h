#include "aeten/lang.h"

#undef aeten_lang__interface
#define aeten_lang__interface(iface, ...) iface
#undef aeten_lang__implementation
#define aeten_lang__implementation(impl, iface) iface
#if defined(AETEN_LANG_INTERFACE)
	#define _AETEN_LANG_IFACE(prefix, suffix) _AETEN_LANG_IFACE_1(prefix, AETEN_LANG_INTERFACE, suffix)
	#define _AETEN_LANG_IFACE_1(prefix, iface, suffix) _AETEN_LANG_IFACE_2(prefix, iface, suffix)
	#define _AETEN_LANG_IFACE_2(prefix, iface, suffix) prefix##iface##suffix

	#undef aeten_lang__interface
	#define aeten_lang__interface(iface, ...) iface

	struct _AETEN_LANG_IFACE(, _st);
	typedef struct _AETEN_LANG_IFACE(, _st) AETEN_LANG_INTERFACE;
	/* {{{ Method structure */
	typedef struct _AETEN_LANG_IFACE(_, _st) {
		#define aeten_lang__method(type, name, ...) \
			type (*name)(AETEN_LANG_INTERFACE*, ##__VA_ARGS__);
		AETEN_LANG_METHODS
		#undef aeten_lang__method
		#undef aeten_lang__interface
		#define aeten_lang__interface(iface, ...) __VA_ARGS__
		#undef _aeten_lang__as_inherit
		#define _aeten_lang__as_inherit(iface) \
			struct _##iface##_st;
		AETEN_FOR_EACH(_aeten_lang__as_inherit, AETEN_LANG_INTERFACE)
		#undef aeten_lang__interface
		#define aeten_lang__interface(iface, ...) iface
	} _AETEN_LANG_IFACE(_, _t);
	/* }}} */

	#undef aeten_lang__interface
	#define aeten_lang__interface(iface, ...) \
		_aeten_lang__define_type(iface, ##__VA_ARGS__)
	AETEN_LANG_INTERFACE
	#undef aeten_lang__interface
	#define aeten_lang__interface(iface, ...) iface

	/* {{{ Method definition */
	#define aeten_lang__method(type, nm, ...) \
		typedef type (*_AETEN_LANG_IFACE(_, __##nm##_t))(AETEN_LANG_INTERFACE*, ##__VA_ARGS__); \
		static void (_AETEN_LANG_IFACE(_, __##nm##_constr))(void) __attribute__((constructor)); \
		static void (_AETEN_LANG_IFACE(_, __##nm##_constr))(void) { \
			char *types[] = AETEN_STRING_OF_EACH(type, ##__VA_ARGS__); \
			size_t sizes[] = AETEN_SIZE_OF_EACH(type, ##__VA_ARGS__); \
			_aeten_lang__method_construct(AETEN_STRINGIZE(AETEN_LANG_INTERFACE), #nm,  types, sizes); \
		}
	AETEN_LANG_METHODS
	#undef aeten_lang__method
	/* }}} */


	#if defined(AETEN_LANG_IMPLEMENTATION_H) && !defined(AETEN_LANG_REQUIRE)
		#define _AETEN_LANG_IMPL(prefix, suffix) _AETEN_LANG_IMPL_1(prefix, AETEN_LANG_IMPLEMENTATION_H, suffix)
		#define _AETEN_LANG_IMPL_1(prefix, impl, suffix) _AETEN_LANG_IMPL_2(prefix, impl, suffix)
		#define _AETEN_LANG_IMPL_2(prefix, impl, suffix) prefix##impl##suffix
		#undef aeten_lang__implementation
		#define aeten_lang__implementation(impl, iface) impl
		#undef  aeten_lang__constructor
		void _AETEN_LANG_IMPL(_, _AETEN_LANG_IFACE(_, __init_interface)) (void* instance);
		#undef  aeten_lang__method
		#define aeten_lang__method(type, mthd, ...) \
			type _AETEN_LANG_IMPL(, __##mthd)(AETEN_LANG_INTERFACE*, ##__VA_ARGS__);
		AETEN_LANG_METHODS
		//void impl##__init(impl*)
		#ifdef AETEN_LANG_IMPLEMENTATION_C
			#undef  aeten_lang__method
			#define aeten_lang__method(type, mthd, ...) \
				instance->mthd = _AETEN_LANG_IMPL(, __##mthd); offset += sizeof(instance->mthd);
			void _AETEN_LANG_IMPL(_, _AETEN_LANG_IFACE(_, __init_interface)) (void* ref) {
				struct _AETEN_LANG_IFACE(_, _st)* instance = (struct _AETEN_LANG_IFACE(_, _st)*)ref;
				memset(instance, 0, sizeof(struct _AETEN_LANG_IFACE(_, _st)));
				unsigned long int offset = 0;
				/* methods */
				AETEN_LANG_METHODS
				#undef  aeten_lang__init_legacy
				#define aeten_lang__init_legacy(iface) _AETEN_LANG_IMPL(_, _##iface##__init_interface)((void*)(((unsigned long int) instance) + offset));
				#undef aeten_lang__interface
				#define aeten_lang__interface(iface, ...) __VA_ARGS__
					AETEN_FOR_EACH(aeten_lang__init_legacy, AETEN_LANG_INTERFACE)
			}
		#endif
	#endif
	#undef _AETEN_LANG_IMPL
	#undef _AETEN_LANG_IMPL_1
	#undef _AETEN_LANG_IMPL_2


	#ifndef AETEN_LANG_IMPLEMENTATION_H
		#undef AETEN_LANG_METHODS
		#undef AETEN_LANG_INTERFACE
	#else

		#undef aeten_lang__interface
		#define aeten_lang__interface(iface, ...) iface
		#undef aeten_lang__implementation
		#define aeten_lang__implementation(impl, iface) iface
		#if defined(AETEN_LANG_IMPLEMENTATION_H) && (AETEN_LANG_IMPLEMENTATION_H != AETEN_LANG_INTERFACE)
			#undef AETEN_LANG_METHODS
			#undef AETEN_LANG_INTERFACE
		#endif
		#undef aeten_lang__implementation
	#endif

	#undef aeten_lang__method
	#undef aeten_lang__interface
	#undef AETEN_LANG_REQUIRE
#endif
