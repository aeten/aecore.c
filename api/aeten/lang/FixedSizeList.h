#pragma once

#include <stddef.h>

#define AETEN_LANG_IMPLEMENTATION_H \
	aeten_lang__implementation(aeten_lang__FixedSizeList, aeten_lang__List)

#define AETEN_LANG_PRIVATE \
	aeten_lang__private(size_t length, size_t element_size, void *elements)

#define AETEN_LANG_CONSTRUCTORS \
	aeten_lang__constructor(size_t /*element_size*/, size_t /*length*/)

#include "aeten/lang/List.h"
#include "aeten/lang/implementation.h"
