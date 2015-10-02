#ifndef _AETEN_LANG_COPYONWRITEARRAYLIST_H
#define _AETEN_LANG_COPYONWRITEARRAYLIST_H

#include <stddef.h>

#define AETEN_LANG_IMPLEMENTATION_H \
	aeten_lang__implementation(aeten_lang__CopyOnWriteArrayList, aeten_lang__List) \
	aeten_lang__constructor(size_t element_size, size_t initial_capacity) \
	aeten_lang__private(size_t capacity, size_t size, size_t element_size, void *elements)


#include "aeten/lang/List.h"
#include "aeten/lang/implementation.h"

#endif
