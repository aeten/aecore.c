#ifndef AETEN_LANG_H
#define AETEN_LANG_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "aeten/lang/FOR_EACH.h"
#include "aeten/lang/export.h"

typedef struct aeten_lang__interface_st aeten_lang__interface_t;
typedef struct aeten_lang__class_st aeten_lang__class_t;
typedef struct aeten_lang__method_definition_st aeten_lang__method_definition_t;
typedef struct aeten_lang__method_implementation_st aeten_lang__method_implementation_t;
typedef struct aeten_lang__type_st aeten_lang__type_t;
typedef struct aeten_lang__object_header_st aeten_lang__object_header_t;
typedef void(*aeten_lang__initializer_t)(aeten_lang__interface_t*);
typedef void(*aeten_lang__finalizer_t)(aeten_lang__interface_t*);


struct aeten_lang__type_st {
	char const *name;
	size_t size;
};

struct aeten_lang__interface_st {
	char const *name;
	aeten_lang__method_definition_t *methods;
	aeten_lang__interface_t **parents;
};

#define aeten_lang__object_header \
	aeten_lang__interface_t *interface; \
	aeten_lang__initializer_t initialize; \
	aeten_lang__finalizer_t finalize;

struct aeten_lang__object_header_st {
	aeten_lang__object_header
};

struct aeten_lang__method_definition_st {
	aeten_lang__interface_t const *interface;
	char const * name;
	aeten_lang__type_t signature[];
};

struct aeten_lang__method_implementation_st {
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

#define _AETEN_REF_OF_EACH_IFACE(iface) &iface##_i,

// TODO: fill Interface structure with methods
#define _aeten_lang__define_type(iface, iface_name, ...) \
	typedef struct iface##_st iface_name; \
	static aeten_lang__interface_t iface##_i; \
	_aeten_lang__constructor(_##iface_name##_c) { \
		_aeten_lang__construct(&iface##_i, #iface_name, (aeten_lang__interface_t*[]){ AETEN_FOR_EACH(_AETEN_REF_OF_EACH_IFACE, __VA_ARGS__) (aeten_lang__interface_t*)NULL }); \
	} \
	_aeten_lang__destructor(_##iface_name##_d) { \
		free(iface##_i.parents); \
	}

#define aeten_lang__implementation(implementation, ...) \
	typedef struct implementation##__private_st implementation##__private_t; \
	typedef struct _##implementation##_ms {} _##implementation##_m; \
	static _##implementation##_m _##implementation##_methods; \
	_aeten_lang__define_type(_##implementation, implementation, __VA_ARGS__); \
	struct _##implementation##_st

#define aeten_lang__interface(iface, ...) \
	_aeten_lang__define_type(iface, iface, __VA_ARGS__); \
	_aeten_lang__destructor(_##iface##__##nm##_d) { \
		free(iface##_i.methods); \
	}; \
	struct iface##_st

#define aeten_lang__object__init(implementation, instance, ...) do { \
	memset(instance, 0, sizeof(implementation)); \
	instance->interface = &_##implementation##_i; \
	instance->initialize = (aeten_lang__initializer_t)implementation##__initialize; \
	instance->finalize = (aeten_lang__finalizer_t)implementation##__finalize; \
} while (0)


#define aeten_lang__method(iface, type, nm, ...) \
	typedef type (*iface##__##nm##_t)(__VA_ARGS__); \
	_aeten_lang__constructor(_##iface##__##nm##_constr) { \
		char * signature_types[] = AETEN_STRING_OF_EACH(type, __VA_ARGS__); \
		size_t signature_sizes[] = AETEN_SIZE_OF_EACH(type, __VA_ARGS__); \
		_aeten_lang__method_construct(&iface##_i, #nm, signature_types, signature_sizes); \
	}

#define aeten_lang__new(iface, ...) \
	iface##__new(__VA_ARGS__)

#define aeten_lang__init(iface, ...) \
	iface AETEN_FIRST_ARG(__VA_ARGS__); \
	iface##__init(&__VA_ARGS__);

#define aeten_lang__delete(object) do { \
	object->finalize((aeten_lang__interface_t*)object); \
	free(object); \
} while(0)

// TODO: check instance interfaces before
#define aeten_lang__cast_ref(type, object) ((type*) object)

#endif // AETEN_LANG_H
