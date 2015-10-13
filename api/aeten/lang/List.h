#ifndef T
	#define T void*
#endif

#include "aeten/lang/Iterable.h"

#include "aeten/lang/start-interface.h"
#define AETEN_LANG_INTERFACE \
	aeten_lang__interface(List, Iterable)

#define AETEN_LANG_METHODS \
	/** Returns the number of elements in this list. */ \
	aeten_lang__method(size_t, size); \
	\
	/** Returns the element at the specified position in this list. */ \
	aeten_lang__method(T, get, unsigned int /* position */); \
	\
	/** Replaces the element at the specified position in this list with the specified element. */ \
	aeten_lang__method(void, set, unsigned int /* position */, T /* element */); \
	\
	/** Appends the specified element to the end of this list. */ \
	aeten_lang__method(void, add, T /* element */);

#if !defined(_AETEN_LANG_LIST_H) || defined(AETEN_LANG_PARAMETRIZED_TYPE)
	#ifndef _AETEN_LANG_LIST_H
		#define _AETEN_LANG_LIST_H
	#endif
	#include "aeten/lang/end-interface.h"
#endif

#undef T
