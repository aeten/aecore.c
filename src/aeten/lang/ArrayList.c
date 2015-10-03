#define AETEN_LANG_IMPLEMENTATION_C
#include "aeten/lang/ArrayList.h"

aeten_lang__List * aeten_lang__ArrayList__new(size_t element_size, size_t length) {
	aeten_lang__ArrayList *list = (aeten_lang__ArrayList *) calloc(1, sizeof(aeten_lang__ArrayList));
	return aeten_lang__cast_ref(aeten_lang__List, aeten_lang__ArrayList__initialize(list, element_size, length));
}

aeten_lang__List * aeten_lang__ArrayList__initialize(aeten_lang__ArrayList *list, size_t element_size, size_t length) {
	_aeten_lang__ArrayList__init(list);
	list->_private.elements = calloc(length, element_size);
	list->_private.length = length;
	list->_private.element_size = element_size;
	return aeten_lang__cast_ref(aeten_lang__List, list);
}

void aeten_lang__ArrayList__finalize(aeten_lang__ArrayList *list) {
	free(list->_private.elements);
}

void aeten_lang__ArrayList__set(aeten_lang__List *list, unsigned int position, void *element) {
	aeten_lang__ArrayList *array_list = aeten_lang__cast_ref(aeten_lang__ArrayList, list);
	if(position >= array_list->_private.length) {
		// TODO: throw exception
	}
	unsigned long pointer = (unsigned long)array_list->_private.elements;
	pointer += position*array_list->_private.element_size;
	memcpy((void*)pointer, element, array_list->_private.element_size);
}

void * aeten_lang__ArrayList__get(aeten_lang__List *list, unsigned int position) {
	aeten_lang__ArrayList *array_list = aeten_lang__cast_ref(aeten_lang__ArrayList, list);
	if(position >= array_list->_private.length) {
		// TODO: throw exception
	}
	unsigned long pointer = (unsigned long)array_list->_private.elements;
	pointer += position*array_list->_private.element_size;
	return (void*)pointer;
}

void aeten_lang__ArrayList__add(aeten_lang__List *list, void *element) {
	// TODO: throw unsupported exception
}

size_t aeten_lang__ArrayList__size(aeten_lang__List *list) {
	return aeten_lang__cast_ref(aeten_lang__ArrayList, list)->_private.length;
}

