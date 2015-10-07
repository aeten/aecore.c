#include "aeten/lang/ArrayList.h"
#include "aeten/lang/Exception.h"
#include "aeten/lang.h"

aeten_lang__ArrayList* _aeten_lang__interfaces = NULL;

void _aeten_lang__init() {
	if (!_aeten_lang__interfaces) {
		_aeten_lang__interfaces = calloc(1, sizeof(aeten_lang__ArrayList));
		_aeten_lang__ArrayList__init(_aeten_lang__interfaces, sizeof(aeten_lang__interface_t), 20);
	}
}

aeten_lang__interface_t* aeten_lang__get_interface(const char* iface_name) {
	unsigned int i;
	size_t size = aeten_lang__cast_and_call(_aeten_lang__interfaces, aeten_lang__List, size);
	for (i=0; i < size; ++i) {
		aeten_lang__interface_t* iface = aeten_lang__cast_and_call(_aeten_lang__interfaces, aeten_lang__List, get, i);
		if (0 == strcmp(iface->name, iface_name)) {
			return iface;
		}
	}
	return NULL;
}



void _aeten_lang__construct(aeten_lang__interface_t *iface, char const *iface_name, aeten_lang__interface_t *ifc_list[]) {
	unsigned int i;
	size_t size;
	if (aeten_lang__get_interface(iface_name)) return;
	for (size=0; ifc_list[size] ; ++size) { }
	iface->name = iface_name;
	AETEN_DEBUG("Register %s(%x) size=%u", iface->name, iface, size);
	iface->parents = (aeten_lang__ParentsList*)aeten_lang__ArrayList__new(sizeof(aeten_lang__interface_t), size);
	for (i=0; i < size && ifc_list[i]; ++i) {
		AETEN_DEBUG("\t%s(%x) inherits from %s(%x)", iface->name, iface, ifc_list[i]->name, ifc_list[i]);
		aeten_lang__cast_and_call(iface->parents, aeten_lang__List, add, ifc_list[i]);
	}
	iface->methods = (aeten_lang__MethodsList*)aeten_lang__ArrayList__new(sizeof(aeten_lang__method_definition_t), 0);
	aeten_lang__cast_and_call(_aeten_lang__interfaces, aeten_lang__List, add, iface);
}

char *_aeten_lang__join_strings(char *dest, char* src[], char join) {
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

void _aeten_lang__method_construct(aeten_lang__interface_t *iface, char const *name, char *signature_types[], size_t signature_sizes[]) {
	int i;
	size_t size;
	for (i=0; i<iface->methods->size(iface->methods); ++i) {
		if (0==strcmp(name, ((aeten_lang__method_definition_t*)iface->methods->get(iface->methods, i))->name)) return;
	}

	for (size=0; signature_types[size]; ++size);
	AETEN_DEBUG("Adds method %s.%s(%s): %s", iface->name, name, AETEN_DEBUG_JOIN_STRINGS(signature_types+1, ','), *signature_types, size);

	aeten_lang__method_definition_t method = {
		iface,
		name,
		(aeten_lang__Signature*) aeten_lang__ArrayList__new(sizeof(aeten_lang__type_t), size)
	};
	for (i=0; i<size; ++i) {
		aeten_lang__type_t type = { signature_types[i], signature_sizes[i] };
		aeten_lang__cast_and_call(method.signature, aeten_lang__List, add, (void*)&type);
	}
	aeten_lang__cast_and_call(iface->methods, aeten_lang__List, add, (void*)&method);
}
