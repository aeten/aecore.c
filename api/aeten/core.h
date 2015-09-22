#ifndef AETEN_CORE_H
#define AETEN_CORE_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#if defined(__cplusplus)
	struct aeten_core_construct { aeten_core_construct(void (*f)(void)) { f(); } };
#	define aeten_core_constructor(fn) \
		static void fn(void); \
		static aeten_core_construct aeten_core_constructor_##fn(fn); \
		void fn()

#else
#	if defined(__GNUC__)
#		define aeten_core_constructor(fn) \
			static void fn(void) __attribute__((constructor)); \
			static void fn(void)

#	elif defined(_MSC_VER)
#		define aeten_core_constructor(fn) \
			static void __cdecl fn(void); \
			__declspec(allocate(".CRT$XCU")) void (__cdecl *fn##_)(void) = fn; \
			static void __cdecl fn(void)
#	endif
#endif

#if defined(aeten_core_constructor) && !defined(aeten_core_destructor)
#	define aeten_core_destructor(fn) \
		static void fn(void);\
		aeten_core_constructor(aeten_core_destructor_##fn) { \
			atexit( fn ); \
		} \
		static void fn(void)
#endif

typedef struct interface_s {
	char const *name;
	struct interface_s *parent;
} aeten_core_interface;

#define _aeten_core__define_type(itfc, itfc_name, ...) \
	static aeten_core_interface itfc; \
	aeten_core_constructor(_##itfc_name##_c) { \
		aeten_core_interface ifc_list[] = {__VA_ARGS__};\
		int i, size = sizeof(ifc_list)/sizeof(aeten_core_interface); \
		itfc.name = #itfc_name; \
		itfc.parent = (aeten_core_interface*) calloc(size+1, sizeof(aeten_core_interface)); \
		for (i=0; i < size; ++i) { \
			itfc.parent[i] = ifc_list[i]; \
		} \
		itfc.parent[size] = (aeten_core_interface){0, 0}; \
	} \
	aeten_core_destructor(_##itfc_name##_d) { \
		free(itfc.parent); \
	}

#define impl(implementation, ...) \
	_aeten_core__define_type(_##implementation##_i, implementation, __VA_ARGS__); \
	typedef struct _##implementation##_s implementation; \
	struct _##implementation##_s

#define interface(itfc, ...) \
	_aeten_core__define_type(itfc, itfc, __VA_ARGS__)

#define _aeten_core__object__impl \
	aeten_core_interface interface;

#define _aeten_core__object__new(implementation, object, ...) \
	object->interface = _##implementation##_i

#endif // AETEN_CORE_H
