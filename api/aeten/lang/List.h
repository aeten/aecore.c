/* Already included by aeten/lang.h */
#ifndef _AETEN_LANG_H
#	include "aeten/lang.h"
#else
#	ifndef _AETEN_LANG_LIST_H
#	define _AETEN_LANG_LIST_H

#define aeten_lang__List__init(implementation, instance) do { \
	instance->size = implementation##__size; \
	instance->get = implementation##__get; \
	instance->set = implementation##__set; \
	instance->add = implementation##__add; \
} while (0);

#define aeten_lang__List__methods(iface) \
	size_t (*size)(iface*); \
	void*  (*get) (iface*, unsigned int); \
	void   (*set) (iface*, unsigned int, void*); \
	void   (*add) (iface*, void*);

aeten_lang__interface(aeten_lang__List);

/** Returns the number of elements in this list. */
aeten_lang__method(aeten_lang__List, size_t, size);

/** Returns the element at the specified position in this list. */
aeten_lang__method(aeten_lang__List, void*, get, unsigned int /* position */);

/** Replaces the element at the specified position in this list with the specified element. */
aeten_lang__method(aeten_lang__List, void, set, unsigned int /* position */, void* /* element */);

/** Appends the specified element to the end of this list. */
aeten_lang__method(aeten_lang__List, void, add, void* /* element */);

#	endif
#endif
