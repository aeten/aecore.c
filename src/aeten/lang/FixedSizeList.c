#define AETEN_LANG_IMPLEMENTATION_C
#include "aeten/lang/FixedSizeList.h"
#include "aeten/lang/IndexOutOfBoundException.h"

void aeten_lang__FixedSizeList__initialize(aeten_lang__FixedSizeList *list, size_t element_size, size_t length) {
	list->_private.elements = calloc(length, element_size);
	list->_private.length = length;
	list->_private.element_size = element_size;
}

void aeten_lang__FixedSizeList__finalize(aeten_lang__FixedSizeList *list) {
	free(list->_private.elements);
}

void aeten_lang__FixedSizeList__set(aeten_lang__FixedSizeList *list, unsigned int position, void *element) {
	if(position >= list->_private.length) {
		aeten_lang__check(position < list->_private.length, aeten_lang__IndexOutOfBoundException, "position=", position, "array.length=", list->_private.length);
	}
	unsigned long pointer = (unsigned long)list->_private.elements;
	pointer += position*list->_private.element_size;
	memcpy((void*)pointer, element, list->_private.element_size);
}

void * aeten_lang__FixedSizeList__get(aeten_lang__FixedSizeList *list, unsigned int position) {
	if(position >= list->_private.length) {
		aeten_lang__check(position < list->_private.length, aeten_lang__IndexOutOfBoundException, "position=", position, "array.length=", list->_private.length);
	}
	unsigned long pointer = (unsigned long)list->_private.elements;
	pointer += position*list->_private.element_size;
	return (void*)pointer;
}

size_t aeten_lang__FixedSizeList__size(aeten_lang__FixedSizeList *list) {
	return list->_private.length;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void aeten_lang__FixedSizeList__add(aeten_lang__FixedSizeList *list, void *element) {
	// TODO: throw unsupported exception
}

aeten_lang__Iterator* aeten_lang__FixedSizeList__iterator(aeten_lang__FixedSizeList *list) {
	return NULL; //TODO
}
#pragma GCC diagnostic pop
