#include "aeten/lang.h"

void _aeten_lang__construct(aeten_lang__interface_t *iface, char const *iface_name, aeten_lang__interface_t *ifc_list[]) {
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

void _aeten_lang__method_construct(aeten_lang__interface_t *iface, char const *name, char *_signature_types[], size_t _signature_sizes[]) {
	int size, signature_names_size, i, j;
	char **signature_types = _signature_types;
	size_t *signature_sizes = _signature_sizes;
	AETEN_DEBUG("Adds method %s.%s(%s): %s", iface->name, name, AETEN_DEBUG_JOIN_STRINGS(signature_types+1, ','), signature_types[0]);

	for (size=0; iface->methods[size].signature && iface->methods[size].signature->name; ++size) { }
	for (signature_names_size=0, i=0; signature_types[i]; ++i, ++signature_names_size) {}

/*	aeten_lang__method_definition_t *methods = (aeten_lang__method_definition_t*) calloc(1, (1 + ++size) * sizeof(aeten_lang__method_definition_t*) + size*sizeof(aeten_lang__method_definition_t));

	aeten_lang__type_t signature;
	for (i=0; i<size-1; ++i) {
		for (j=0; iface->methods[i].signature[j].name; ++j) {
			for (signature_names_size=0, i=0; signature_types[i]; ++i, ++signature_names_size) {}
			signature = iface->methods[i].signature[j];
//			calloc()
//			methods[i].signature[j].name = iface->methods[i].signature[j].name;
//			methods[i].signature[j].size = iface->methods[i].signature[j].size;
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
*/
}
