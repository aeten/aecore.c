#include <stdio.h>

#include "aeten/lang/IndexOutOfBoundException.h"
#include "aeten/lang/PThreadReadWriteLock.h"
#include "aeten/lang/RuntimeError.h"

#define AETEN_LANG_IMPLEMENTATION_C
#include "aeten/lang/CopyOnWriteArrayList.h"

#define _get_lock(action) \
	action##_lock(list->_private.rw_lock);

#define LOCK(action) do { \
		Lock* lock = list->_private.rw_lock->_get_lock(action); \
		lock->lock(lock); \
	} while (0);

#define UNLOCK(action) do { \
		Lock* lock = list->_private.rw_lock->_get_lock(action); \
		lock->unlock(lock); \
	} while (0);

#define check_with_lock(lock_action, expression, exception, message_format, ...) \
	do { \
		if (!(expression)) { \
			UNLOCK(lock_action); \
			char* message = aeten_lang__string_from_format(message_format, ##__VA_ARGS__); \
			char* prefixed_message = aeten_lang__string_from_format("%s +%u: Check (%s): %s (%s)", __func__, __LINE__, #expression, #exception, message); \
			Throwable__throw(exception##__new(prefixed_message)); \
			free(prefixed_message); /* TODO: move it into finally block */ \
			free(message); /* TODO: move it into finally block */ \
		} \
	} while (0);

inline void CopyOnWriteArrayList__initialize(CopyOnWriteArrayList *list, size_t element_size) {
	aeten_lang__array_t* array =  (aeten_lang__array_t*)calloc(1, sizeof(aeten_lang__array_t));
	array->elements = NULL;
	array->length = 0;
	array->element_size = element_size;
	list->_private.rw_lock = PThreadReadWriteLock__new();
	LOCK(write);
	list->_private.array = array;
	UNLOCK(write);
}

inline void CopyOnWriteArrayList__finalize(CopyOnWriteArrayList *list) {
	LOCK(write);
	free(list->_private.array->elements);
	free(list->_private.array);
	UNLOCK(write);
	delete(list->_private.rw_lock);
}

inline void CopyOnWriteArrayList__set(CopyOnWriteArrayList *list, unsigned int position, void *element) {
	aeten_lang__array_t* array = list->_private.array;
	LOCK(write);
	check_with_lock(write, position < array->length, IndexOutOfBoundException, "position=%u; array.length=%u", position, array->length);
	unsigned long pointer = (unsigned long)array->elements;
	pointer += position*array->element_size;
	memcpy((void*)pointer, element, array->element_size);
	UNLOCK(write);
}

inline void * CopyOnWriteArrayList__get(CopyOnWriteArrayList *list, unsigned int position) {
	aeten_lang__array_t* array = list->_private.array;
	LOCK(read);
	check_with_lock(read, position < array->length, IndexOutOfBoundException, "position=%u; array.length=%u", position, array->length);
	unsigned long pointer = (unsigned long)array->elements;
	pointer += position*array->element_size;
	UNLOCK(read);
	return (void*)pointer;
}

inline void CopyOnWriteArrayList__add(CopyOnWriteArrayList *list, void *element) {
	aeten_lang__array_t* array = list->_private.array;
	LOCK(write);
	aeten_lang__array_t* new_array =  (aeten_lang__array_t*)calloc(1, sizeof(aeten_lang__array_t));
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
	UNLOCK(write);
}

inline size_t CopyOnWriteArrayList__size(CopyOnWriteArrayList *list) {
	aeten_lang__array_t* array = list->_private.array;
	LOCK(read);
	size_t size = array->length;
	UNLOCK(read);
	return size;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
inline Iterator* CopyOnWriteArrayList__iterator(CopyOnWriteArrayList *list) {
	return NULL; //TODO
}
#pragma GCC diagnostic pop
