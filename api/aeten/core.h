#ifndef AETEN_CORE_H
#define AETEN_CORE_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#if defined(__GNUC__)
#	define aeten_core_constructor(fn) \
		static void fn(void) __attribute__((constructor)); \
		static void fn(void)
#elif defined(_MSC_VER)
#	define aeten_core_constructor(fn) \
		static void __cdecl fn(void); \
		__declspec(allocate(".CRT$XCU")) void (__cdecl *fn##_)(void) = fn; \
		static void __cdecl fn(void)
#endif

#if defined(aeten_core_constructor) && !defined(aeten_core_destructor)
#	define aeten_core_destructor(fn) \
		static void fn(void);\
		aeten_core_constructor(aeten_core_destructor_##fn) { \
			atexit( fn ); \
		} \
		static void fn(void)
#endif

typedef struct aeten_interface_s aeten_interface;
typedef struct aeten_method_s aeten_method;
struct aeten_interface_s {
	char const *name;
	aeten_method **methods;
	aeten_interface **parents;
};
struct aeten_method_s {
	aeten_interface const *interface;
	char const * name;
	void const * type;
};

#define _aeten_core__define_type(iface, iface_name, ...) \
	static aeten_interface iface; \
	aeten_core_constructor(_##iface_name##_c) { \
		aeten_interface *ifc_list[] = {__VA_ARGS__};\
		int i; \
		size_t size = sizeof(ifc_list)/sizeof(aeten_interface*); \
		iface.name = #iface_name; \
		iface.parents = (aeten_interface**) malloc(size+1* sizeof(aeten_interface**)); \
		for (i=0; i < size; ++i) { \
			iface.parents[i] = ifc_list[i]; \
		} \
		iface.parents[size] = NULL; \
		iface.methods = (aeten_method**) calloc(1, sizeof(aeten_method**)); \
	} \
	aeten_core_destructor(_##iface_name##_d) { \
		free(iface.parents); \
	}

#define impl(implementation, ...) \
	typedef struct _##implementation##_ms {} _##implementation##_m; \
	static _##implementation##_m _##implementation##_methods;\
	_aeten_core__define_type(_##implementation##_i, implementation, __VA_ARGS__); \
	typedef struct _##implementation##_s implementation; \
	struct _##implementation##_s

#define interface(iface, ...) \
	_aeten_core__define_type(iface, iface, __VA_ARGS__); \
	aeten_core_destructor(_##iface##__##nm##_d) { \
		free(iface.methods); \
	}

#define _aeten_core__object__impl \
	aeten_interface *interface;

#define _aeten_core__object__new(implementation, instance, ...) \
	memset(instance, 0, sizeof(implementation)); \
	instance->interface = & _##implementation##_i; \

#define method(iface, type, nm, ...) \
	typedef type (*iface##__##nm##_t)(__VA_ARGS__); \
	static aeten_method iface##__##nm = (aeten_method) { \
		&iface, \
		#nm, \
		NULL \
	}; \
	aeten_core_constructor(_##iface##__##nm##_c) { \
		int size; \
		for (size=0; iface.methods[size]; ++size) {} \
		iface.methods = (aeten_method**) realloc(iface.methods, (++size+1)*(sizeof(aeten_method*))); \
		iface.methods[size-1] = &iface##__##nm; \
		iface.methods[size] = NULL; \
	}


interface(Enum)
method(Enum, int, value)

#endif // AETEN_CORE_H
