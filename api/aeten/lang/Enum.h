#include "aeten/lang/start-interface.h"
#define AETEN_LANG_INTERFACE \
	aeten_lang__interface(Enum)

#define AETEN_LANG_METHODS \
	aeten_lang__method(int, value);

#ifndef _AETEN_LANG_ENUM_H
	#define _AETEN_LANG_ENUM_H
	#include "aeten/lang/end-interface.h"
#endif
