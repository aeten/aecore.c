#include "aeten/lang/ArrayList.h"

aeten_lang__ArrayList * aeten_lang__ArrayList__new(size_t element_size, size_t length) {
	aeten_lang__ArrayList *list = (aeten_lang__ArrayList *) calloc(1, sizeof(aeten_lang__ArrayList));
	return aeten_lang__ArrayList__init(list, element_size, length);
}

aeten_lang__ArrayList * aeten_lang__ArrayList__init(aeten_lang__ArrayList *list, size_t element_size, size_t length) {
	_aeten_lang__object__new(aeten_lang__ArrayList, list);
	list->elements = calloc(length, element_size);
	list->length = length;
	list->element_size = element_size;
	return list;
}

void aeten_lang__ArrayList__finalize(aeten_lang__ArrayList *list) {
	free(list->elements);
}

void aeten_lang__ArrayList__set(aeten_lang__ArrayList *list, unsigned int position, void *element) {
	if(position >= list->length) {
		// TODO: throw exception
	}
	unsigned long pointer = (unsigned long)list->elements;
	pointer += position*list->element_size;
	memcpy((void*)pointer, element, list->element_size);
}

void * aeten_lang__ArrayList__get(aeten_lang__ArrayList *list, unsigned int position) {
	if(position >= list->length) {
		// TODO: throw exception
	}
	unsigned long pointer = (unsigned long)list->elements;
	pointer += position*list->element_size;
	return (void*)pointer;
}

void aeten_lang__ArrayList__add(aeten_lang__ArrayList *list, void *element) {
	// TODO: throw unsupported exception
}

size_t aeten_lang__ArrayList__size(aeten_lang__ArrayList *list) {
	list->length;
}

