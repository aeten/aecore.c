#ifndef AETEN_LANG_ENUM_H
#define AETEN_LANG_ENUM_H

#include "aeten/lang/import.h"

#define AETEN_LANG_IMPLEMENTATION_H \
	aeten_lang__interface(aeten_lang__Enum)

#define AETEN_LANG_METHODS \
	aeten_lang__method(int, value);

#include "aeten/lang/interface.h"

#endif // AETEN_LANG_ENUM_H
