#ifndef AETEN_LANG_ENUM_H
#define AETEN_LANG_ENUM_H

#include "aeten/lang/import.h"

#define aeten_lang__Enum__init(impl, instance)
#define aeten_lang__Enum__methods(iface) \
	int (*value)(iface*);

aeten_lang__interface(aeten_lang__Enum);
aeten_lang__method(aeten_lang__Enum, int, value);

#endif // AETEN_LANG_ENUM_H
