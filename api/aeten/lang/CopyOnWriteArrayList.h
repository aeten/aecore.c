#ifndef _AETEN_LANG_COW_H
#define _AETEN_LANG_COW_H

/**
 * Thread safe copy on write List implementation.
 */
#define AETEN_LANG_IMPLEMENTATION_H \
	aeten_lang__implementation(CopyOnWriteArrayList, List)

#define AETEN_LANG_PRIVATE \
	aeten_lang__private(aeten_lang__array_t* volatile array)

#define AETEN_LANG_CONSTRUCTORS \
	aeten_lang__constructor(size_t /*element_size*/)

#include "aeten/lang/List.h"
#include "aeten/lang/implementation.h"

#endif
