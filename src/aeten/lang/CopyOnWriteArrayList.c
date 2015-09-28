#include "aeten/lang/CopyOnWriteArrayList.h"

aeten_lang__CopyOnWriteArrayList * aeten_lang__CopyOnWriteArrayList__new(size_t element_size, size_t initial_capacity) {
	aeten_lang__CopyOnWriteArrayList *list = (aeten_lang__CopyOnWriteArrayList *) calloc(1, sizeof(aeten_lang__CopyOnWriteArrayList));
	return aeten_lang__CopyOnWriteArrayList__init(list, element_size, initial_capacity);
}

aeten_lang__CopyOnWriteArrayList * aeten_lang__CopyOnWriteArrayList__init(aeten_lang__CopyOnWriteArrayList *list, size_t element_size, size_t initial_capacity) {
	_aeten_lang__object__new(aeten_lang__CopyOnWriteArrayList, list);
	list->element_size = element_size;
	list->elements = calloc(initial_capacity, element_size);
	list->capacity = initial_capacity;
	list->size = 0;
	return list;
}

void aeten_lang__CopyOnWriteArrayList__finalize(aeten_lang__CopyOnWriteArrayList *list) {
	free(list->elements);
}

void aeten_lang__CopyOnWriteArrayList__set(aeten_lang__CopyOnWriteArrayList *list, unsigned int position, void *element) {
	if(position >= list->size) {
		// TODO: throw exception
	}
	unsigned long pointer = (unsigned long)list->elements;
	pointer += position*list->element_size;
	memcpy((void*)pointer, element, list->element_size);
}

void aeten_lang__CopyOnWriteArrayList__add(aeten_lang__CopyOnWriteArrayList *list, void *element) {
	if (list->capacity == list->size) {
		unsigned int capacity = list->capacity+(1 + ((list->capacity - 1) / 2));
		void* elements = calloc(capacity, list->element_size);
		list->elements = memcpy(elements, list->elements, (list->capacity * list->element_size));
		list->capacity = capacity;
	}
	unsigned long pointer = (unsigned long)list->elements;
	pointer += list->size*list->element_size;
	memcpy((void*)pointer, element, list->element_size);
	list->size = list->size+1;
}

void* aeten_lang__CopyOnWriteArrayList__get(aeten_lang__CopyOnWriteArrayList *list, unsigned int position) {
	if(position >= list->size) {
		// TODO: throw exception
	}
	unsigned long pointer = (unsigned long)list->elements;
	pointer += position*list->element_size;
	return (void*)pointer;
}

size_t aeten_lang__CopyOnWriteArrayList__size(aeten_lang__CopyOnWriteArrayList *list) {
	return list->size;
}

