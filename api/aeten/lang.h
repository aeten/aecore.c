#ifndef AETEN_CORE_H
#define AETEN_CORE_H

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

#ifdef AETEN_DEBUG
#	include<stdio.h>
#	include <assert.h>
#	undef AETEN_DEBUG
	static char* _aeten_debug_tmp_str = 0;
#	define AETEN_DEBUG(format, ...) do { \
		printf("%s +%d: " format "\n", __FILE__, __LINE__, __VA_ARGS__); \
		if (_aeten_debug_tmp_str) { \
			free(_aeten_debug_tmp_str); \
			_aeten_debug_tmp_str = 0; \
		} \
	} while (0)
#	define AETEN_JOIN_STRINGS(src, join) _aeten_lang__join_strings(_aeten_debug_tmp_str, src, join)
#	define ASSERT(...) assert(__VA_ARGS__)

#else
#	define AETEN_DEBUG(...)
#	define AETEN_JOIN_STRINGS(dest, src)
#	define ASSERT(...)
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
	static aeten_lang__interface_t *iface##_parents[] = {__VA_ARGS__}; \
	_aeten_lang__constructor(_##iface_name##_c) { \
		_aeten_lang__construct(&iface, #iface_name, iface##_parents); \
	} \
	_aeten_lang__destructor(_##iface_name##_d) { \
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
	_aeten_lang__destructor(_##iface##__##nm##_d) { \
		free(iface.methods); \
	};

#define _aeten_lang__object__impl \
	aeten_lang__interface_t *interface;

#define _aeten_lang__object__new(implementation, instance, ...) \
	memset(instance, 0, sizeof(implementation)); \
	instance->interface = & _##implementation##_i; 

#define _AETEN_LANG_CB_RETURN_TYPE(ret_type, ...) ret_type
#define _AETEN_LANG_CB_ARGS_TYPE(ret_type, ...) __VA_ARGS__

#define aeten_lang__method(iface, nm, ...) \
	typedef _AETEN_LANG_CB_RETURN_TYPE(__VA_ARGS__) (*iface##__##nm##_t)(_AETEN_LANG_CB_ARGS_TYPE(__VA_ARGS__)); \
	_aeten_lang__constructor(_##iface##__##nm##_constr) { \
		char * signature_types[] = AETEN_STRING_OF_EACH(__VA_ARGS__); \
		size_t signature_sizes[] = AETEN_SIZE_OF_EACH(__VA_ARGS__); \
		_aeten_lang__method_construct(&iface, #nm, signature_types, signature_sizes); \
	}

#define aeten_lang__new(iface, ...) \
	iface##__new(__VA_ARGS__)

#define aeten_lang__init(iface, ...) \
	iface AETEN_FIRST_ARG(__VA_ARGS__); \
	iface##__init(&__VA_ARGS__);


static void _aeten_lang__construct(aeten_lang__interface_t *iface, char const *iface_name, aeten_lang__interface_t *ifc_list[]) {
	int i;
	size_t size = sizeof(ifc_list)/sizeof(aeten_lang__interface_t*);
	iface->name = iface_name;
	iface->parents = (aeten_lang__interface_t**) malloc((size+1) * sizeof(aeten_lang__interface_t*));
	for (i=0; i < size; ++i) {
		iface->parents[i] = ifc_list[i];
	}
	iface->parents[size] = NULL;
	iface->methods = (aeten_lang__method_definition_t*) calloc(1, sizeof(aeten_lang__method_definition_t[1]));
}

static char *_aeten_lang__join_strings(char *dest, char* src[], char join) {
	int size, length, i, offset;
	char* c;
	for (size=0, i=0; src[i]; i++) {
		 size+=(strlen(src[i]+1));
	}
	length = i;
	if (0==dest) dest = malloc(size*sizeof(char)+1);
	for (i=0, offset=0; src[i]; ++i, ++offset) {
		for(c=src[i]; *c; ++c, ++offset) {
			*(char*)(dest + offset) = *c;
		}
		*(char*)(dest + offset) = join;
	}
	*(dest + offset-1) = 0;
	return dest;
}

static void _aeten_lang__method_construct(aeten_lang__interface_t *iface, char const *name, char *_signature_types[], size_t _signature_sizes[]) {
	int size, signature_names_size, i, j;
	char **signature_types = _signature_types;
	size_t *signature_sizes = _signature_sizes;
	AETEN_DEBUG("Adds method %s.%s(%s): %s", iface->name, name, AETEN_JOIN_STRINGS(signature_types+1, ','), signature_types[0]);
	for (size=0; iface->methods[size].signature && iface->methods[size].signature->name; ++size) {}
	for (signature_names_size=0, i=0; signature_types[i]; ++i, ++signature_names_size) {}
	aeten_lang__method_definition_t *methods = (aeten_lang__method_definition_t*) calloc(++size+1, sizeof(aeten_lang__method_definition_t[size+1]) + sizeof(signature_types+1) + sizeof(signature_sizes+1) + (signature_names_size+1)*sizeof(char));
	for (i=0; i<size-1; ++i) {
		for (j=0; iface->methods[i].signature[j].name; ++j) {
			methods[i].signature[j].name = iface->methods[i].signature[j].name;
			methods[i].signature[j].size = iface->methods[i].signature[j].size;
		}
		methods[i].interface = iface->methods[i].interface;
		methods[i].name = iface->methods[i].name;
	}

	free(iface->methods);
	methods[i].interface = iface;
	methods[i].name = name;
	for (j=0; signature_types[j]; j++) {
		methods[i].signature[j].name = signature_types[j];
		methods[i].signature[j].size = signature_sizes[j];
	}
	iface->methods = methods;
}

aeten_lang__interface(aeten_lang__Enum)
aeten_lang__method(aeten_lang__Enum, value, int)

#endif // AETEN_CORE_H
