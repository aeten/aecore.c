#include "aeten/lang/IndexOutOfBoundException.h"

#define AETEN_LANG_IMPLEMENTATION_C
#include "aeten/lang/FixedSizeList.h"

inline void FixedSizeList__initialize(FixedSizeList *list, size_t element_size, size_t length) {
	list->_private.elements = calloc(length, element_size);
	list->_private.length = length;
	list->_private.element_size = element_size;
}

inline void FixedSizeList__finalize(FixedSizeList *list) {
	free(list->_private.elements);
}

inline void FixedSizeList__set(FixedSizeList *list, unsigned int position, void *element) {
	check(position < list->_private.length, IndexOutOfBoundException, "position=", position, "array.length=", list->_private.length);
	unsigned long pointer = (unsigned long)list->_private.elements;
	pointer += position*list->_private.element_size;
	memcpy((void*)pointer, element, list->_private.element_size);
}

inline void * FixedSizeList__get(FixedSizeList *list, unsigned int position) {
	check(position < list->_private.length, IndexOutOfBoundException, "position=", position, "array.length=", list->_private.length);
	unsigned long pointer = (unsigned long)list->_private.elements;
	pointer += position*list->_private.element_size;
	return (void*)pointer;
}

inline size_t FixedSizeList__size(FixedSizeList *list) {
	return list->_private.length;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
inline void FixedSizeList__add(FixedSizeList *list, void *element) {
	// TODO: throw unsupported exception
}

inline Iterator* FixedSizeList__iterator(FixedSizeList *list) {
	return NULL; //TODO
}
#pragma GCC diagnostic pop
