#include "aeten/lang/IndexOutOfBoundException.h"

#define AETEN_LANG_IMPLEMENTATION_C
#include "aeten/lang/CopyOnWriteArrayList.h"

inline void CopyOnWriteArrayList__initialize(CopyOnWriteArrayList *list, size_t element_size) {
	aeten_lang__array_t* volatile array =  (aeten_lang__array_t*)calloc(1, sizeof(aeten_lang__array_t));
	array->elements = NULL;
	array->length = 0;
	array->element_size = element_size;
	list->_private.array = array;
}

inline void CopyOnWriteArrayList__finalize(CopyOnWriteArrayList *list) {
	free(list->_private.array->elements);
	free(list->_private.array);
}

inline void CopyOnWriteArrayList__set(CopyOnWriteArrayList *list, unsigned int position, void *element) {
	aeten_lang__array_t* array = list->_private.array;
	check(position < array->length, IndexOutOfBoundException, "position=%u; array.length=%u", position, array->length);
	unsigned long pointer = (unsigned long)array->elements;
	pointer += position*array->element_size;
	memcpy((void*)pointer, element, array->element_size);
}

inline void * CopyOnWriteArrayList__get(CopyOnWriteArrayList *list, unsigned int position) {
	volatile aeten_lang__array_t* array = list->_private.array;
	check(position < array->length, IndexOutOfBoundException, "position=%u; array.length=%u", position, array->length);
	unsigned long pointer = (unsigned long)array->elements;
	pointer += position*array->element_size;
	return (void*)pointer;
}

inline void CopyOnWriteArrayList__add(CopyOnWriteArrayList *list, void *element) {
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

inline size_t CopyOnWriteArrayList__size(CopyOnWriteArrayList *list) {
	return list->_private.array->length;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
inline Iterator* CopyOnWriteArrayList__iterator(CopyOnWriteArrayList *list) {
	return NULL; //TODO
}
#pragma GCC diagnostic pop
