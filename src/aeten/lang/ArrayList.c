#include "aeten/lang/ArrayList.h"

ArrayList * ArrayList__new(size_t element_size, size_t length) {
	ArrayList *list = (ArrayList *) calloc(1, sizeof(ArrayList));
	return ArrayList__init(list, element_size, length);
}
ArrayList * ArrayList__init(ArrayList *list, size_t element_size, size_t length) {
	_aeten_lang__object__new(ArrayList, list);
	list->elements = calloc(length, element_size);
	list->length = length;
	list->element_size = element_size;
	return list;
}
void ArrayList__finalize(ArrayList *list) {
	free(list->elements);
}
void ArrayList__set(ArrayList *list, int index, void *value) {
	unsigned long pointer = (unsigned long)list->elements;
	pointer += index*list->element_size;
	memcpy((void*)pointer, value, list->element_size);
}
void * ArrayList__get(ArrayList *list, int index) {
	unsigned long pointer = (unsigned long)list->elements;
	pointer += index*list->element_size;
	return (void*) pointer;
}
size_t ArrayList__size(ArrayList *list) {
	list->length;
}

