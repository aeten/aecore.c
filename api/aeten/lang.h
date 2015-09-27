#ifndef AETEN_LANG_H
#define AETEN_LANG_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "aeten/lang/FOR_EACH.h"
#include "aeten/lang/export.h"

typedef struct aeten_lang__interface_s aeten_lang__interface_t;
typedef struct aeten_lang__method_definition_s aeten_lang__method_definition_t;
typedef struct aeten_lang__method_implementation_s aeten_lang__method_implementation_t;
typedef struct aeten_lang__type_s aeten_lang__type_t;

struct aeten_lang__type_s {
	char const *name;
	size_t size;
};

struct aeten_lang__interface_s {
	char const *name;
	aeten_lang__method_definition_t *methods;
	aeten_lang__interface_t **parents;
};

struct aeten_lang__method_definition_s {
	aeten_lang__interface_t const *interface;
	char const * name;
	aeten_lang__type_t signature[];
};

struct aeten_lang__method_implementation_s {
	aeten_lang__method_definition_t *definition;
	void *implementation;
};

void _aeten_lang__construct(aeten_lang__interface_t *iface, char const *iface_name, aeten_lang__interface_t *ifc_list[]);
char *_aeten_lang__join_strings(char *dest, char* src[], char join);
void _aeten_lang__method_construct(aeten_lang__interface_t *iface, char const *name, char *_signature_types[], size_t _signature_sizes[]);


#define AETEN_COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#ifdef AETEN_DEBUG
#	include<stdio.h>
#	include <assert.h>
#	undef AETEN_DEBUG
	static char* _aeten_debug_tmp_str = 0;
#	define AETEN_DEBUG(format, ...) do { \
		fprintf(stderr, "%s +%d: " format "\n", __FILE__, __LINE__, __VA_ARGS__); \
		if (_aeten_debug_tmp_str) { \
			free(_aeten_debug_tmp_str); \
			_aeten_debug_tmp_str = 0; \
		} \
	} while (0)
#	define AETEN_DEBUG_JOIN_STRINGS(src, join) _aeten_lang__join_strings(_aeten_debug_tmp_str, src, join)
#	define AETEN_DEBUG_ASSERT(...) assert(__VA_ARGS__)

#else
#	define AETEN_DEBUG(...)
#	define AETEN_DEBUG_JOIN_STRINGS(dest, src)
#	define AETEN_DEBUG_ASSERT(...)
#endif

#if defined(__GNUC__)
#	define _aeten_lang__constructor(fn) \
		static void fn(void) __attribute__((constructor)); \
		static void fn(void)
#elif defined(_MSC_VER)
#	define _aeten_lang__constructor(fn) \
		static void __cdecl fn(void); \
		__declspec(allocate(".CRT$XCU")) void (__cdecl *fn##_)(void) = fn; \
		static void __cdecl fn(void)
#endif

#if defined(_aeten_lang__constructor) && !defined(_aeten_lang__destructor)
#	define _aeten_lang__destructor(fn) \
		static void fn(void);\
		_aeten_lang__constructor(_aeten_lang__destructor_##fn) { \
			atexit( fn ); \
		} \
		static void fn(void)
#endif

#define aeten_lang__type_of(a) \
  ((aeten_lang__type_t) { #a, sizeof(a) })

#define _aeten_lang__define_type(iface, iface_name, ...) \
	static aeten_lang__interface_t iface; \
	_aeten_lang__constructor(_##iface_name##_c) { \
		_aeten_lang__construct(&iface, #iface_name, AETEN_REF_OF_EACH(aeten_lang__interface_t, __VA_ARGS__)); \
	} \
	_aeten_lang__destructor(_##iface_name##_d) { \
		free(iface.parents); \
	}

#define aeten_lang__implementation(implementation, ...) \
	typedef struct _##implementation##_ms {} _##implementation##_m; \
	static _##implementation##_m _##implementation##_methods; \
	_aeten_lang__define_type(_##implementation##_i, implementation, __VA_ARGS__); \
	typedef struct _##implementation##_s implementation; \
	struct _##implementation##_s

#define aeten_lang__interface(iface, ...) \
	_aeten_lang__define_type(iface, iface, __VA_ARGS__); \
	_aeten_lang__destructor(_##iface##__##nm##_d) { \
		free(iface.methods); \
	};

#define _aeten_lang__object__impl \
	aeten_lang__interface_t *interface; \
	void * finalize;

//	void (*(void*))() finalize;

#define _aeten_lang__object__new(implementation, instance, ...) do { \
	memset(instance, 0, sizeof(implementation)); \
	instance->interface = & _##implementation##_i; \
	instance->finalize = implementation##__finalize; \
} while (0)

#define aeten_lang__method(iface, type, nm, ...) \
	typedef type (*iface##__##nm##_t)(__VA_ARGS__); \
	_aeten_lang__constructor(_##iface##__##nm##_constr) { \
		char * signature_types[] = AETEN_STRING_OF_EACH(type, __VA_ARGS__); \
		size_t signature_sizes[] = AETEN_SIZE_OF_EACH(type, __VA_ARGS__); \
		_aeten_lang__method_construct(&iface, #nm, signature_types, signature_sizes); \
	}

#define aeten_lang__new(iface, ...) \
	iface##__new(__VA_ARGS__)

#define aeten_lang__init(iface, ...) \
	iface AETEN_FIRST_ARG(__VA_ARGS__); \
	iface##__init(&__VA_ARGS__);

#define aeten_lang__delete(object) do { \
	((void (*)())object->finalize)(object); \
	free(object); \
} while(0)

#endif // AETEN_LANG_H
