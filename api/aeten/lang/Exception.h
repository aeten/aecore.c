#include <signal.h>
#include "aeten/lang/Closable.h"
#undef AETEN_LANG_INTERFACE
#undef AETEN_LANG_METHODS

#define AETEN_LANG_INTERFACE \
	aeten_lang__interface(aeten_lang__Exception)

#define AETEN_LANG_METHODS \
	aeten_lang__method(char*, message); \
	aeten_lang__method(void, print_message);

#ifndef _AETEN_LANG_EXCEPTION_H
#define _AETEN_LANG_EXCEPTION_H

#include "aeten/lang/interface.h"

#endif
