#include "aeten/lang.h"

#undef aeten_lang__interface
#define aeten_lang__interface(iface, ...) iface
#undef aeten_lang__implementation
#define aeten_lang__implementation(impl, iface) iface
#define AETEN_LANG_IFACE(prefix, suffix) AETEN_LANG_IFACE_1(prefix, AETEN_LANG_INTERFACE, suffix)
#define AETEN_LANG_IFACE_1(prefix, iface, suffix) AETEN_LANG_IFACE_2(prefix, iface, suffix)
#define AETEN_LANG_IFACE_2(prefix, iface, suffix) prefix##iface##suffix

#ifndef AETEN_LANG_INTERFACE
	#error AETEN_LANG_INTERFACE must be defined
#endif

#ifdef AETEN_LANG_PARAMETRIZED_TYPE
	typedef struct {
		aeten_lang__implementation_t* _implementation;
		#define aeten_lang__method(type, name, ...) \
			type (*name)(void*, ##__VA_ARGS__);
		AETEN_LANG_METHODS
		#undef aeten_lang__method
		#undef aeten_lang__interface
		#define aeten_lang__interface(iface, ...) __VA_ARGS__
		#undef _aeten_lang__as_inherit
		#define _aeten_lang__as_inherit(iface) \
			iface*                        _as__##iface; \
			aeten_lang__implementation_t* _##iface##__impl; \
			struct                        _##iface##_st;
		AETEN_FOR_EACH(_aeten_lang__as_inherit, AETEN_LANG_INTERFACE)
		#undef aeten_lang__interface
		#define aeten_lang__interface(iface, ...) iface
	} AETEN_LANG_PARAMETRIZED_TYPE;
	#undef AETEN_LANG_PARAMETRIZED_TYPE

#else
	#undef aeten_lang__interface
	#define aeten_lang__interface(iface, ...) iface

	typedef struct AETEN_LANG_IFACE(, _st) AETEN_LANG_INTERFACE;

	/* {{{ Method structure */
	struct AETEN_LANG_IFACE(_, _st) {
		#define aeten_lang__method(type, name, ...) \
			type (*name)(void*, ##__VA_ARGS__);
		AETEN_LANG_METHODS
		#undef aeten_lang__method
		#undef aeten_lang__interface
		#define aeten_lang__interface(iface, ...) __VA_ARGS__
		#undef _aeten_lang__as_inherit
		#define _aeten_lang__as_inherit(iface) \
			iface*                        _as__##iface; \
			aeten_lang__implementation_t* _##iface##__impl; \
			struct                        _##iface##_st;
		AETEN_FOR_EACH(_aeten_lang__as_inherit, AETEN_LANG_INTERFACE)
		#undef aeten_lang__interface
		#define aeten_lang__interface(iface, ...) iface
	};
	/* }}} */

	struct AETEN_LANG_IFACE(, _st) {
		aeten_lang__implementation_t* _implementation;
		struct AETEN_LANG_IFACE(_, _st);
	};

	#undef aeten_lang__interface
	#define aeten_lang__interface(iface, ...) \
		_aeten_lang__define_type(iface, ##__VA_ARGS__)
	AETEN_LANG_INTERFACE
	#undef aeten_lang__interface
	#define aeten_lang__interface(iface, ...) iface

	/* {{{ Method definition */
	#define aeten_lang__method(type, nm, ...) \
		typedef type (*AETEN_LANG_IFACE(_, __##nm##_t))(AETEN_LANG_INTERFACE*, ##__VA_ARGS__); \
		static void (AETEN_LANG_IFACE(_, __##nm##_constr))(void) __attribute__((constructor)); \
		static void (AETEN_LANG_IFACE(_, __##nm##_constr))(void) { \
			char *types[] = AETEN_STRING_OF_EACH(type, ##__VA_ARGS__); \
			size_t sizes[] = AETEN_SIZE_OF_EACH(type, ##__VA_ARGS__); \
			_aeten_lang__method_construct(AETEN_STRINGIZE(AETEN_LANG_INTERFACE), #nm,  types, sizes); \
		}
	AETEN_LANG_METHODS
	#undef aeten_lang__method
	/* }}} */


	#if defined(AETEN_LANG_IMPLEMENTATION_H) && !defined(AETEN_LANG_REQUIRE)
		#define AETEN_LANG_IMPL(prefix, suffix) AETEN_LANG_IMPL_1(prefix, AETEN_LANG_IMPLEMENTATION_H, suffix)
		#define AETEN_LANG_IMPL_1(prefix, impl, suffix) AETEN_LANG_IMPL_2(prefix, impl, suffix)
		#define AETEN_LANG_IMPL_2(prefix, impl, suffix) prefix##impl##suffix
		#undef aeten_lang__implementation
		#define aeten_lang__implementation(impl, iface) impl
		#undef  aeten_lang__constructor
		typedef struct AETEN_LANG_IMPL(, _st) AETEN_LANG_IMPLEMENTATION_H;
		void AETEN_LANG_IMPL(_, AETEN_LANG_IFACE(_, __init_interface)) (aeten_lang__implementation_t* implementation, unsigned long int* offset);
		#undef  aeten_lang__method
		#define aeten_lang__method(type, mthd, ...) \
			type AETEN_LANG_IMPL(, __##mthd)(AETEN_LANG_IMPLEMENTATION_H*, ##__VA_ARGS__);
		AETEN_LANG_METHODS

		#ifdef AETEN_LANG_IMPLEMENTATION_C

			#define aeten_lang__arg_1(i, x) x arg_##i
			#define aeten_lang__arg_2(i, x) arg_##i
			#define aeten_lang__arg_3(...) aeten_lang__arg_4(__VA_ARGS__)
			#define aeten_lang__arg_4(...) __VA_ARGS__

			#define aeten_lang__arg_ref(ref, ...) aeten_lang__arg_ref_1(ref, ##__VA_ARGS__)
			#define aeten_lang__arg_ref_1(ref, ...) aeten_lang__arg_ref_2((*((aeten_lang__implementation_t**)ref))->instance, ##__VA_ARGS__)
			#define aeten_lang__arg_ref_2(ref, ...) ref, ##__VA_ARGS__

			#undef  aeten_lang__method
			#define aeten_lang__method(type, mthd, ...) \
				type AETEN_LANG_IMPL(_, __##mthd##_)(aeten_lang__arg_3(AETEN_FOR_EACH_I(aeten_lang__arg_1, void*, ##__VA_ARGS__))); \
				type AETEN_LANG_IMPL(_, __##mthd##_)(aeten_lang__arg_3(AETEN_FOR_EACH_I(aeten_lang__arg_1, void*, ##__VA_ARGS__))) { \
					return AETEN_LANG_IMPL(, __##mthd)(aeten_lang__arg_ref(AETEN_FOR_EACH_I(aeten_lang__arg_2, void*, ##__VA_ARGS__))); \
				}
			AETEN_LANG_METHODS
			#undef  aeten_lang__method
			#define aeten_lang__method(type, mthd, ...) \
				as_iface->mthd = AETEN_LANG_IMPL(_, __##mthd##_); (*offset) += sizeof(as_iface->mthd);

			void AETEN_LANG_IMPL(_, AETEN_LANG_IFACE(_, __init_interface)) (aeten_lang__implementation_t* implementation, unsigned long int* offset) {
				struct AETEN_LANG_IFACE(, _st)* as_iface = (struct AETEN_LANG_IFACE(, _st)*)(((unsigned long int) implementation->instance) + (*offset));
				as_iface->_implementation = implementation;
				(*offset) += sizeof(as_iface->_implementation);
				/* methods */
				AETEN_LANG_METHODS
				#undef aeten_lang__interface
				#define aeten_lang__interface(iface, ...) __VA_ARGS__
				#undef  aeten_lang__init_legacy
				#define aeten_lang__init_legacy(iface) \
					(*offset) += sizeof(as_iface->_as__##iface); \
					as_iface->_as__##iface = (void*)(((unsigned long int) implementation->instance) + (*offset)); \
					AETEN_LANG_IMPL(_, _##iface##__init_interface)(implementation, offset);
				AETEN_FOR_EACH(aeten_lang__init_legacy, AETEN_LANG_INTERFACE)
			}

			#undef aeten_lang__arg_1
			#undef aeten_lang__arg_2
			#undef aeten_lang__arg_3
			#undef aeten_lang__arg_4
			#undef aeten_lang__arg_ref
			#undef aeten_lang__arg_ref_1
			#undef aeten_lang__arg_ref_2

		#endif
	#endif
	#undef AETEN_LANG_IMPL
	#undef AETEN_LANG_IMPL_1
	#undef AETEN_LANG_IMPL_2


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
	#endif

	#undef aeten_lang__implementation
	#undef aeten_lang__method
	#undef aeten_lang__interface
	#undef AETEN_LANG_REQUIRE
	#undef AETEN_LANG_IFACE
	#undef AETEN_LANG_IFACE_1
	#undef AETEN_LANG_IFACE_2
#endif
