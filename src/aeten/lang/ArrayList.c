#include "aeten/lang/Exception.h"
#include "aeten/lang/IndexOutOfBoundException.h"

#define AETEN_LANG_IMPLEMENTATION_C

#include "aeten/lang/ArrayList.h"

aeten_lang__List * aeten_lang__ArrayList__initialize(aeten_lang__ArrayList *list, size_t element_size, size_t initial_capacity) {
	list->_private.element_size = element_size;
	if (initial_capacity>0) {
		list->_private.elements = calloc(initial_capacity, element_size);
	}
	list->_private.capacity = initial_capacity;
	list->_private.size = 0;
	return aeten_lang__cast_ref(aeten_lang__List, list);
}

void aeten_lang__ArrayList__finalize(aeten_lang__ArrayList *list) {
	if (list && list->_private.elements) {
		free(list->_private.elements);
		list->_private.elements = NULL;
	}
}

void aeten_lang__ArrayList__set(aeten_lang__List *list, unsigned int position, void *element) {
	aeten_lang__ArrayList *array_list = aeten_lang__cast_ref(aeten_lang__ArrayList, list);
	if(position >= array_list->_private.size) {
		aeten_lang__check(position < array_list->_private.size, aeten_lang__IndexOutOfBoundException, "position=%u; array.length=%u", position, array_list->_private.size);
	}
	unsigned long pointer = (unsigned long)array_list->_private.elements;
	pointer += position*array_list->_private.element_size;
	memcpy((void*)pointer, element, array_list->_private.element_size);
}

void aeten_lang__ArrayList__add(aeten_lang__List *list, void *element) {
	aeten_lang__ArrayList *array_list = aeten_lang__cast_ref(aeten_lang__ArrayList, list);
	if (array_list->_private.capacity == array_list->_private.size) {
		unsigned int capacity = ((array_list->_private.capacity * 3) / 2) + 1;
		void* elements = calloc(capacity, array_list->_private.element_size);
		array_list->_private.elements = memcpy(elements, array_list->_private.elements, (array_list->_private.capacity * array_list->_private.element_size));
		array_list->_private.capacity = capacity;
	}
	unsigned long pointer = (unsigned long)array_list->_private.elements;
	pointer += array_list->_private.size*array_list->_private.element_size;
	memcpy((void*)pointer, element, array_list->_private.element_size);
	array_list->_private.size++;
}

void* aeten_lang__ArrayList__get(aeten_lang__List *list, unsigned int position) {
	aeten_lang__ArrayList *array_list = aeten_lang__cast_ref(aeten_lang__ArrayList, list);
	if(position >= array_list->_private.size) {
		aeten_lang__check(position < array_list->_private.size, aeten_lang__IndexOutOfBoundException, "position=%u; array.length=%u", position, array_list->_private.size);
	}
	unsigned long pointer = (unsigned long)array_list->_private.elements;
	pointer += position*array_list->_private.element_size;
	return (void*)pointer;
}

size_t aeten_lang__ArrayList__size(aeten_lang__List *list) {
	return aeten_lang__cast_ref(aeten_lang__ArrayList, list)->_private.size;
}
