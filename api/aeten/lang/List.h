#ifndef AETEN_LANG_LIST_H
#define AETEN_LANG_LIST_H

#include "aeten/lang/import.h"

#define aeten_lang__List__init(implementation, instance) do { \
	instance->size = implementation##__size; \
	instance->get = implementation##__get; \
	instance->set = implementation##__set; \
	instance->add = implementation##__add; \
} while (0);

#define aeten_lang__List__header(implementation) \
	object_header; \
	size_t (*size)(aeten_lang__List*); \
	void*  (*get)  (aeten_lang__List*, unsigned int); \
	void   (*set)  (aeten_lang__List*, unsigned int, void*); \
	void   (*add)  (aeten_lang__List*, void*);

interface(aeten_lang__List) {
	aeten_lang__List__header(aeten_lang__List)
};

/** Returns the number of elements in this list. */
method(aeten_lang__List, size_t, size);

/** Returns the element at the specified position in this list. */
method(aeten_lang__List, void*, get, unsigned int /* position */);

/** Replaces the element at the specified position in this list with the specified element. */
method(aeten_lang__List, void, set, unsigned int /* position */, void* /* element */);

/** Appends the specified element to the end of this list. */
method(aeten_lang__List, void, add, void* /* element */);

#endif
