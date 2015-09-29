#ifndef AETEN_LANG_ENUM_H
#define AETEN_LANG_ENUM_H

#include "aeten/lang/import.h"

#define aeten_lang__Enum__init(implementation, instance)
#define aeten_lang__Enum__methods(iface) \
	int (*value)(iface*);

interface(aeten_lang__Enum);
method(aeten_lang__Enum, int, value);

#endif // AETEN_LANG_ENUM_H
