#include "aeten/lang/CopyOnWriteArrayList.h"

aeten_lang__List * aeten_lang__CopyOnWriteArrayList__new(size_t element_size, size_t initial_capacity) {
	aeten_lang__CopyOnWriteArrayList *list = (aeten_lang__CopyOnWriteArrayList *) calloc(1, sizeof(aeten_lang__CopyOnWriteArrayList));
	aeten_lang__CopyOnWriteArrayList__initialize(list, element_size, initial_capacity);
	return aeten_lang__cast_ref(aeten_lang__List, list);
}

aeten_lang__CopyOnWriteArrayList * aeten_lang__CopyOnWriteArrayList__initialize(aeten_lang__CopyOnWriteArrayList *list, size_t element_size, size_t initial_capacity) {
	aeten_lang__object__init(aeten_lang__CopyOnWriteArrayList, list);
	aeten_lang__List__init(aeten_lang__CopyOnWriteArrayList, list);
	list->_private.element_size = element_size;
	list->_private.elements = calloc(initial_capacity, element_size);
	list->_private.capacity = initial_capacity;
	list->_private.size = 0;
	return list;
}

void aeten_lang__CopyOnWriteArrayList__finalize(aeten_lang__List *list) {
	free(aeten_lang__cast_ref(aeten_lang__CopyOnWriteArrayList, list)->_private.elements);
}

void aeten_lang__CopyOnWriteArrayList__set(aeten_lang__List *list, unsigned int position, void *element) {
	aeten_lang__CopyOnWriteArrayList *cow_list = aeten_lang__cast_ref(aeten_lang__CopyOnWriteArrayList, list);
	if(position >= cow_list->_private.size) {
		// TODO: throw exception
	}
	unsigned long pointer = (unsigned long)cow_list->_private.elements;
	pointer += position*cow_list->_private.element_size;
	memcpy((void*)pointer, element, cow_list->_private.element_size);
}

void aeten_lang__CopyOnWriteArrayList__add(aeten_lang__List *list, void *element) {
	aeten_lang__CopyOnWriteArrayList *cow_list = aeten_lang__cast_ref(aeten_lang__CopyOnWriteArrayList, list);
	if (cow_list->_private.capacity == cow_list->_private.size) {
		unsigned int capacity = cow_list->_private.capacity+(1 + ((cow_list->_private.capacity - 1) / 2));
		void* elements = calloc(capacity, cow_list->_private.element_size);
		cow_list->_private.elements = memcpy(elements, cow_list->_private.elements, (cow_list->_private.capacity * cow_list->_private.element_size));
		cow_list->_private.capacity = capacity;
	}
	unsigned long pointer = (unsigned long)cow_list->_private.elements;
	pointer += cow_list->_private.size*cow_list->_private.element_size;
	memcpy((void*)pointer, element, cow_list->_private.element_size);
	cow_list->_private.size++;
}

void* aeten_lang__CopyOnWriteArrayList__get(aeten_lang__List *list, unsigned int position) {
	aeten_lang__CopyOnWriteArrayList *cow_list = aeten_lang__cast_ref(aeten_lang__CopyOnWriteArrayList, list);
	if(position >= cow_list->_private.size) {
		// TODO: throw exception
	}
	unsigned long pointer = (unsigned long)cow_list->_private.elements;
	pointer += position*cow_list->_private.element_size;
	return (void*)pointer;
}

size_t aeten_lang__CopyOnWriteArrayList__size(aeten_lang__List *list) {
	return aeten_lang__cast_ref(aeten_lang__CopyOnWriteArrayList, list)->_private.size;
}

