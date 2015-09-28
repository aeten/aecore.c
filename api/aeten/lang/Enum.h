#ifndef AETEN_LANG_ENUM_H
#define AETEN_LANG_ENUM_H

#include "aeten/lang/import.h"

aeten_lang__interface(aeten_lang__Enum) {
	object_header;
};

aeten_lang__method(aeten_lang__Enum, int, value);

#endif // AETEN_LANG_ENUM_H
