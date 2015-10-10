#define AETEN_LANG_IMPLEMENTATION_C
#include "aeten/lang/CopyOnWriteArrayList.h"
#include "aeten/lang/IndexOutOfBoundException.h"

void aeten_lang__CopyOnWriteArrayList__initialize(aeten_lang__CopyOnWriteArrayList *list, size_t element_size) {
	aeten_lang__array_t* volatile array =  (aeten_lang__array_t*)calloc(1, sizeof(aeten_lang__array_t));
	array->elements = NULL;
	array->length = 0;
	array->element_size = element_size;
	list->_private.array = array;
}

void aeten_lang__CopyOnWriteArrayList__finalize(aeten_lang__CopyOnWriteArrayList *list) {
	free(list->_private.array->elements);
	free(list->_private.array);
}

void aeten_lang__CopyOnWriteArrayList__set(aeten_lang__CopyOnWriteArrayList *list, unsigned int position, void *element) {
	aeten_lang__array_t* array = list->_private.array;
	if(position >= array->length) {
		aeten_lang__check(position < array->length, aeten_lang__IndexOutOfBoundException, "position=%u; array.length=%u", position, array->length);
	}
	unsigned long pointer = (unsigned long)array->elements;
	pointer += position*array->element_size;
	memcpy((void*)pointer, element, array->element_size);
}

void * aeten_lang__CopyOnWriteArrayList__get(aeten_lang__CopyOnWriteArrayList *list, unsigned int position) {
	volatile aeten_lang__array_t* array = list->_private.array;
	if(position >= array->length) {
		aeten_lang__check(position < array->length, aeten_lang__IndexOutOfBoundException, "position=%u; array.length=%u", position, array->length);
	}
	unsigned long pointer = (unsigned long)array->elements;
	pointer += position*array->element_size;
	return (void*)pointer;
}

void aeten_lang__CopyOnWriteArrayList__add(aeten_lang__CopyOnWriteArrayList *list, void *element) {
	aeten_lang__array_t* volatile array = list->_private.array;
	aeten_lang__array_t* volatile new_array =  (aeten_lang__array_t*)calloc(1, sizeof(aeten_lang__array_t));
	new_array->length = array->length+1;
	new_array->element_size = array->element_size;
	new_array->elements = malloc(new_array->element_size * new_array->length);
	if (array->length>0) {
		memcpy(new_array->elements, array->elements, array->element_size * array->length);
	}

	unsigned long pointer = (unsigned long)new_array->elements;
	pointer += array->length * new_array->element_size;
	memcpy((void*)pointer, element, new_array->element_size);
	list->_private.array = new_array;

	if (array->elements) {
		free(array->elements);
	}
	free(array);
}

size_t aeten_lang__CopyOnWriteArrayList__size(aeten_lang__CopyOnWriteArrayList *list) {
	return list->_private.array->length;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
aeten_lang__Iterator* aeten_lang__CopyOnWriteArrayList__iterator(aeten_lang__CopyOnWriteArrayList *list) {
	return NULL; //TODO
}
#pragma GCC diagnostic pop
