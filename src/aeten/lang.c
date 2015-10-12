#include "aeten/lang/ArrayList.h"
#include "aeten/lang/Throwable.h"
#include "aeten/lang.h"

#ifdef AETEN_DEBUG
#	include<stdio.h>
#	include <assert.h>
#	undef AETEN_DEBUG
#	define AETEN_DEBUG(format, ...) do { \
		static char* _aeten_debug_tmp_str = 0; \
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

/* TODO: Use a Map when will be implemented */
static List* _interfaces_list = NULL;

void _aeten_lang__init(void) {
	if (!_interfaces_list) {
		ArrayList* list = calloc(1, sizeof(ArrayList));
		_ArrayList__init(list, sizeof(aeten_lang__interface_t), 20);
		_interfaces_list = list->_as__List;
	}
}

aeten_lang__interface_t* aeten_lang__get_interface(const char* iface_name) {
	unsigned int i;
	size_t size = _interfaces_list->size(_interfaces_list);
	for (i=0; i < size; ++i) {
		aeten_lang__interface_t* iface = _interfaces_list->get(_interfaces_list, i);
		if (0 == strcmp(iface->name, iface_name)) {
			return iface;
		}
	}
	return NULL;
}



void _aeten_lang__construct(char const *iface_name, aeten_lang__interface_t *ifc_list[]) {
	unsigned int i;
	size_t size;
	if (aeten_lang__get_interface(iface_name)) return;
	aeten_lang__interface_t iface;
	for (size=0; ifc_list[size] ; ++size) { }
	iface.name = iface_name;
	AETEN_DEBUG("Register %s(%lx)", iface.name, (unsigned long int)&iface);
	iface.parents = (aeten_lang__ParentsList*)ArrayList__new(sizeof(aeten_lang__interface_t), size);
	for (i=0; i < size && ifc_list[i]; ++i) {
		AETEN_DEBUG("\t%s(%lx) inherits from %s(%lx)", iface.name, (unsigned long int)&iface, ifc_list[i]->name, (unsigned long int)ifc_list[i]);
		((List*)iface.parents)->add(iface.parents, ifc_list[i]);
	}
	iface.methods = (aeten_lang__MethodsList*)ArrayList__new(sizeof(aeten_lang__method_definition_t), 0);
	_interfaces_list->add(_interfaces_list, &iface);
}

char *_aeten_lang__join_strings(char *dest, char* src[], char join) {
	int size, i, offset;
	char* c;
	for (size=0, i=0; src[i]; i++) {
		 size+=(strlen(src[i]+1));
	}
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

void _aeten_lang__method_construct(char const *iface_name, char const *name, char *signature_types[], size_t signature_sizes[]) {
	unsigned int i;
	size_t size;
	aeten_lang__interface_t* iface = aeten_lang__get_interface(iface_name);
	for (i=0; i<iface->methods->size(iface->methods); ++i) {
		if (0==strcmp(name, (iface->methods->get(iface->methods, i))->name)) return;
	}

	for (size=0; signature_types[size]; ++size);
	AETEN_DEBUG("Adds method %s.%s(%s): %s", iface->name, name, AETEN_DEBUG_JOIN_STRINGS(signature_types+1, ','), *signature_types);

	aeten_lang__method_definition_t method = {
		iface,
		name,
		(aeten_lang__Signature*) ArrayList__new(sizeof(aeten_lang__type_t), size)
	};
	for (i=0; i<size; ++i) {
		aeten_lang__type_t type = { signature_types[i], signature_sizes[i] };
		((List*)method.signature)->add(method.signature, &type);
	}
	((List*)iface->methods)->add(iface->methods, (void*)&method);
}

aeten_lang__interface_t* aeten_lang__interface_of(void* instance) {
	return aeten_lang__get_interface((*(aeten_lang__implementation_t**)instance)->interface);
}
