
#ifndef _AETEN_LANG_H
#define _AETEN_LANG_H
#if !defined(__GNUC__) || (__GNUC__ < 4)
#error "Æten lang requires GCC >= 4"
#endif

#ifdef _aeten_lang_IMPORT
#include "aeten/lang/export.h"
#endif


#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "aeten/lang/String.h"
#include "aeten/lang/FOR_EACH.h"

typedef struct aeten_lang__interface_st             aeten_lang__interface_t;
typedef struct aeten_lang__method_definition_st     aeten_lang__method_definition_t;
typedef struct aeten_lang__method_implementation_st aeten_lang__method_implementation_t;
typedef struct aeten_lang__type_st                  aeten_lang__type_t;
typedef struct aeten_lang__implementation_st        aeten_lang__implementation_t;
typedef struct aeten_lang__Signature_st             aeten_lang__Signature;
typedef struct aeten_lang__MethodsList_st           aeten_lang__MethodsList;
typedef struct aeten_lang__ParentsList_st           aeten_lang__ParentsList;
typedef struct aeten_lang__array_st                 aeten_lang__array_t;


typedef void   (*aeten_lang__initializer_t) (aeten_lang__interface_t*);
typedef void   (*aeten_lang__finalizer_t)   (aeten_lang__interface_t*);


struct aeten_lang__type_st {
	char const *name;
	size_t size;
};

struct aeten_lang__array_st {
	size_t length;
	size_t element_size;
	void*  elements;
};

struct aeten_lang__interface_st {
	char const *name;
	aeten_lang__MethodsList* methods;
	aeten_lang__ParentsList* parents;
};


struct aeten_lang__implementation_st {
	char*                   interface;
	void*                   instance;
	size_t                  size;
	aeten_lang__finalizer_t finalize;
};

struct aeten_lang__Signature_st {
	aeten_lang__implementation_t* _implementation;
	size_t (*size)(aeten_lang__Signature*);
	aeten_lang__type_t*  (*get) (aeten_lang__Signature*, unsigned int);
};

struct aeten_lang__MethodsList_st {
	aeten_lang__implementation_t* _implementation;
	size_t (*size)(aeten_lang__MethodsList*);
	aeten_lang__method_definition_t*  (*get) (aeten_lang__MethodsList*, unsigned int);
};

struct aeten_lang__ParentsList_st {
	aeten_lang__implementation_t* _implementation;
	size_t (*size)(aeten_lang__ParentsList*);
	aeten_lang__interface_t*  (*get) (aeten_lang__ParentsList*, unsigned int);
};

struct aeten_lang__method_definition_st {
	aeten_lang__interface_t const *interface;
	char const * name;
	aeten_lang__Signature *signature;
};

struct aeten_lang__method_implementation_st {
	aeten_lang__method_definition_t *definition;
	void *implementation;
};

void _aeten_lang__construct(char const *iface, aeten_lang__interface_t *ifc_list[]);
char *_aeten_lang__join_strings(char *dest, char* src[], char join);
void _aeten_lang__method_construct(char const *iface, char const *name, char *signature_types[], size_t signature_sizes[]);
aeten_lang__interface_t* aeten_lang__get_interface(const char* iface_name);
aeten_lang__interface_t* aeten_lang__interface_of(void* instance);

#define delete(object) do { \
		object->_implementation->finalize((aeten_lang__interface_t*)object); \
		free(object->_implementation); \
	} while(0)


#define call(object_ref, method, ...) \
	object_ref->method(object_ref, ##__VA_ARGS__)

#define cast(type, object_ref) (object_ref->_as__##type)


#define aeten_lang__type_of(a) \
	((aeten_lang__type_t) { #a, sizeof(a) })


#define _AETEN_REF_OF_EACH_IFACE(iface) aeten_lang__get_interface(#iface),
#define _aeten_lang__define_type(iface, ...) \
	static void _##iface##_c(void) __attribute__((constructor)) ; \
	static void _##iface##_c(void) { \
		_aeten_lang__construct(#iface, (aeten_lang__interface_t*[]) { \
			AETEN_FOR_EACH(_AETEN_REF_OF_EACH_IFACE, ##__VA_ARGS__) (aeten_lang__interface_t*)NULL \
		}); \
	}

void _aeten_lang__init(void);
__attribute__((constructor)) static void _aeten_lang__init_c(void) {
	_aeten_lang__init();
}

#endif // AETEN_LANG_H
