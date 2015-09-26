#ifndef AETEN_CORE_H
#define AETEN_CORE_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

typedef struct aeten_lang__interface_s aeten_lang__interface;
typedef struct aeten_lang__method_s aeten_lang__method;

#if defined(__GNUC__)
#	define aeten_lang__constructor(fn) \
		static void fn(void) __attribute__((constructor)); \
		static void fn(void)
#elif defined(_MSC_VER)
#	define aeten_lang__constructor(fn) \
		static void __cdecl fn(void); \
		__declspec(allocate(".CRT$XCU")) void (__cdecl *fn##_)(void) = fn; \
		static void __cdecl fn(void)
#endif

#if defined(aeten_lang__constructor) && !defined(aeten_lang__destructor)
#	define aeten_lang__destructor(fn) \
		static void fn(void);\
		aeten_lang__constructor(aeten_lang__destructor_##fn) { \
			atexit( fn ); \
		} \
		static void fn(void)
#endif

struct aeten_lang__interface_s {
	char const *name;
	aeten_lang__method *methods;
	aeten_lang__interface **parents;
};
struct aeten_lang__method_s {
	aeten_lang__interface const *interface;
	char const * name;
	void const * type;
};

#define _aeten_lang__define_type(iface, iface_name, ...) \
	static aeten_lang__interface iface; \
	aeten_lang__constructor(_##iface_name##_c) { \
		int i; \
		aeten_lang__interface *ifc_list[] = {__VA_ARGS__}; \
		size_t size = sizeof(ifc_list)/sizeof(aeten_lang__interface*); \
		iface.name = #iface_name; \
		iface.parents = (aeten_lang__interface**) malloc((size+1) * sizeof(aeten_lang__interface*)); \
		for (i=0; i < size; ++i) { \
			iface.parents[i] = ifc_list[i]; \
		} \
		iface.parents[size] = NULL; \
		iface.methods = (aeten_lang__method*) calloc(1, sizeof(aeten_lang__method[1])); \
	} \
	aeten_lang__destructor(_##iface_name##_d) { \
		free(iface.parents); \
	}

#define aeten_lang__implementation(implementation, ...) \
	typedef struct _##implementation##_ms {} _##implementation##_m; \
	static _##implementation##_m _##implementation##_methods;\
	_aeten_lang__define_type(_##implementation##_i, implementation, __VA_ARGS__); \
	typedef struct _##implementation##_s implementation; \
	struct _##implementation##_s

#define aeten_lang__interface(iface, ...) \
	_aeten_lang__define_type(iface, iface, __VA_ARGS__); \
	aeten_lang__destructor(_##iface##__##nm##_d) { \
		free(iface.methods); \
	}

#define _aeten_lang__object__impl \
	aeten_lang__interface *interface;

#define _aeten_lang__object__new(implementation, instance, ...) \
	memset(instance, 0, sizeof(implementation)); \
	instance->interface = & _##implementation##_i; \

#define aeten_lang__method(iface, typ, nm, ...) \
	typedef typ (*iface##__##nm##_t)(__VA_ARGS__); \
	aeten_lang__constructor(_##iface##__##nm##_c) { \
		int size, i; \
		for (size=0; iface.methods[size].name; ++size) {} \
		aeten_lang__method *methods = (aeten_lang__method*) calloc(++size+1, sizeof(aeten_lang__method[size+1])); \
		for (i=0; i<size-1; ++i) { \
			memcpy(&methods[i], &iface.methods[i], sizeof(aeten_lang__method)); \
		} \
		\
		free(iface.methods); \
		methods[size-1].interface = &iface; \
		methods[size-1].name = #nm; \
		methods[size-1].type = NULL; \
		iface.methods = methods; \
	}

aeten_lang__interface(aeten_lang__Enum)
aeten_lang__method(aeten_lang__Enum, int, value)

#endif // AETEN_CORE_H
