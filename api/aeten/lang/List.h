#ifndef AETEN_LANG_LIST_H
#define AETEN_LANG_LIST_H

#include "aeten/lang/import.h"

interface(List);
method(List, size_t, size);
//method(List, void, set, int, void);
method(List, void*, get, int);

#endif
