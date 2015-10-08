#include <stdbool.h>

#include "aeten/lang/start-interface.h"
#define AETEN_LANG_INTERFACE \
	aeten_lang__interface(aeten_lang__Iterable)

#define AETEN_LANG_METHODS \
	aeten_lang__method(bool,  has_next); \
	aeten_lang__method(void*, next); \
	aeten_lang__method(void,  remove);

#ifndef _AETEN_LANG_ITERABLE_H
#define _AETEN_LANG_ITERABLE_H
#include "aeten/lang/end-interface.h"

#endif
