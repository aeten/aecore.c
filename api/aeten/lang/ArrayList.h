#ifndef AETEN_LANG_ARRAYLIST_H
#define AETEN_LANG_ARRAYLIST_H

#include <stddef.h>

#include "aeten/lang.h"
#include "aeten/lang/List.h"


aeten_lang__implementation(aeten_lang__ArrayList, {
	size_t length;
	size_t element_size;
	void *elements;
}, aeten_lang__List);

aeten_lang__ArrayList * aeten_lang__ArrayList__initialize(aeten_lang__ArrayList *list, size_t element_size, size_t length);
aeten_lang__List * aeten_lang__ArrayList__new(size_t element_size, size_t length);

void aeten_lang__ArrayList__finalize(aeten_lang__List *list);

/** @see aeten_lang__List__get  */
void* aeten_lang__ArrayList__get(aeten_lang__List *list, unsigned int position);

/** @see aeten_lang__List__set  */
void aeten_lang__ArrayList__set(aeten_lang__List *list, unsigned int position, void *element);

/** @see aeten_lang__List__add  */
void aeten_lang__ArrayList__add(aeten_lang__List *list, void *element);

/** @see aeten_lang__List__size  */
size_t aeten_lang__ArrayList__size(aeten_lang__List *list);

#endif
