#ifndef AETEN_LANG_ARRAYLIST_H
#define AETEN_LANG_ARRAYLIST_H

#include <stddef.h>

#define AETEN_LANG_IMPLEMENTATION_H \
	aeten_lang__implementation(aeten_lang__ArrayList, aeten_lang__List) \
	aeten_lang__constructor(size_t element_size, size_t length) \
	aeten_lang__private(size_t length, size_t element_size, void *elements)

#include "aeten/lang/List.h"
#include "aeten/lang/implementation.h"

#endif
