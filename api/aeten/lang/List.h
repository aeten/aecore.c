#ifndef AETEN_LANG_LIST_H
#define AETEN_LANG_LIST_H

#include "aeten/lang/import.h"

interface(aeten_lang__List);

/** Returns the number of elements in this list. */
method(aeten_lang__List, size_t, size);

/** Returns the element at the specified position in this list. */
method(aeten_lang__List, void*, get, unsigned int /* position */);

/** Replaces the element at the specified position in this list with the specified element. */
method(aeten_lang__List, void, set, unsigned int /* position */, void* /* element */);

/** Appends the specified element to the end of this list. */
method(aeten_lang__List, void, add, void* /* element */);

#endif
