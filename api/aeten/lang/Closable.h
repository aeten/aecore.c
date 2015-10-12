#include "aeten/lang/start-interface.h"
#define AETEN_LANG_INTERFACE \
	aeten_lang__interface(Closable)

#define AETEN_LANG_METHODS \
	aeten_lang__method(void, close);

#ifndef _AETEN_LANG_CLOSABLE_H
	#define _AETEN_LANG_CLOSABLE_H
	#include "aeten/lang/end-interface.h"
#endif
