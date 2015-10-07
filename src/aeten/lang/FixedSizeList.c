#define AETEN_LANG_IMPLEMENTATION_C
#include "aeten/lang/FixedSizeList.h"

aeten_lang__List * aeten_lang__FixedSizeList__initialize(aeten_lang__FixedSizeList *list, size_t element_size, size_t length) {
	list->_private.elements = calloc(length, element_size);
	list->_private.length = length;
	list->_private.element_size = element_size;
	return aeten_lang__cast_ref(aeten_lang__List, list);
}

void aeten_lang__FixedSizeList__finalize(aeten_lang__FixedSizeList *list) {
	free(list->_private.elements);
}

void aeten_lang__FixedSizeList__set(aeten_lang__List *list, unsigned int position, void *element) {
	aeten_lang__FixedSizeList *array_list = aeten_lang__cast_ref(aeten_lang__FixedSizeList, list);
	if(position >= array_list->_private.length) {
//		aeten_lang__check(position < array.length, aeten_lang__IndexOutOfBoundException, "position=", position, "array.length=", array.length);
	}
	unsigned long pointer = (unsigned long)array_list->_private.elements;
	pointer += position*array_list->_private.element_size;
	memcpy((void*)pointer, element, array_list->_private.element_size);
}

void * aeten_lang__FixedSizeList__get(aeten_lang__List *list, unsigned int position) {
	aeten_lang__FixedSizeList *array_list = aeten_lang__cast_ref(aeten_lang__FixedSizeList, list);
	if(position >= array_list->_private.length) {
//		aeten_lang__check(position < array.length, aeten_lang__IndexOutOfBoundException, "position=", position, "array.length=", array.length);
	}
	unsigned long pointer = (unsigned long)array_list->_private.elements;
	pointer += position*array_list->_private.element_size;
	return (void*)pointer;
}

void aeten_lang__FixedSizeList__add(aeten_lang__List *list, void *element) {
	// TODO: throw unsupported exception
}

size_t aeten_lang__FixedSizeList__size(aeten_lang__List *list) {
	return aeten_lang__cast_ref(aeten_lang__FixedSizeList, list)->_private.length;
}

