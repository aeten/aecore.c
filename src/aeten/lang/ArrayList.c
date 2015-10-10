#include "aeten/lang/Throwable.h"
#include "aeten/lang/IndexOutOfBoundException.h"

#define AETEN_LANG_IMPLEMENTATION_C

#include "aeten/lang/ArrayList.h"

void aeten_lang__ArrayList__initialize(aeten_lang__ArrayList *list, size_t element_size, size_t initial_capacity) {
	list->_private.element_size = element_size;
	if (initial_capacity>0) {
		list->_private.elements = calloc(initial_capacity, element_size);
	}
	list->_private.capacity = initial_capacity;
	list->_private.size = 0;
}

void aeten_lang__ArrayList__finalize(aeten_lang__ArrayList *list) {
	if (list && list->_private.elements) {
		free(list->_private.elements);
		list->_private.elements = NULL;
	}
}

void aeten_lang__ArrayList__set(aeten_lang__ArrayList *list, unsigned int position, void *element) {
	if(position >= list->_private.size) {
		aeten_lang__check(position < list->_private.size, aeten_lang__IndexOutOfBoundException, "position=%u; array.length=%u", position, list->_private.size);
	}
	unsigned long pointer = (unsigned long)list->_private.elements;
	pointer += position*list->_private.element_size;
	memcpy((void*)pointer, element, list->_private.element_size);
}

void aeten_lang__ArrayList__add(aeten_lang__ArrayList *list, void *element) {
	if (list->_private.capacity == list->_private.size) {
		unsigned int capacity = ((list->_private.capacity * 3) / 2) + 1;
		void* elements = calloc(capacity, list->_private.element_size);
		list->_private.elements = memcpy(elements, list->_private.elements, (list->_private.capacity * list->_private.element_size));
		list->_private.capacity = capacity;
	}
	unsigned long pointer = (unsigned long)list->_private.elements;
	pointer += list->_private.size*list->_private.element_size;
	memcpy((void*)pointer, element, list->_private.element_size);
	list->_private.size++;
}

void* aeten_lang__ArrayList__get(aeten_lang__ArrayList *list, unsigned int position) {
	if(position >= list->_private.size) {
		aeten_lang__check(position < list->_private.size, aeten_lang__IndexOutOfBoundException, "position=%u; array.length=%u", position, list->_private.size);
	}
	unsigned long pointer = (unsigned long)list->_private.elements;
	pointer += position*list->_private.element_size;
	return (void*)pointer;
}

size_t aeten_lang__ArrayList__size(aeten_lang__ArrayList *list) {
	return list->_private.size;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
aeten_lang__Iterator* aeten_lang__ArrayList__iterator(aeten_lang__ArrayList *list) {
	return NULL; //TODO
}
#pragma GCC diagnostic pop
