#ifndef AETEN_LANG_ARRAYLIST_H
#define AETEN_LANG_ARRAYLIST_H

#include "aeten/lang/import.h"
#include "aeten/lang/List.h"

implementation(ArrayList, List) {
	_aeten_lang__object__impl
	size_t length;
	size_t element_size;
	void *elements;
};

ArrayList * ArrayList__init(ArrayList *list, size_t element_size, size_t length);
ArrayList * ArrayList__new(size_t element_size, size_t length);
void ArrayList__finalize(ArrayList *list);
void * ArrayList__get(ArrayList *list, int index);
void ArrayList__set(ArrayList *list, int index, void *value);

#endif
