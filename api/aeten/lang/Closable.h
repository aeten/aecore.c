#pragma once

#define AETEN_LANG_IMPLEMENTATION_H \
	aeten_lang__interface(aeten_lang__Closable)

#define AETEN_LANG_METHODS \
	aeten_lang__method(void, close);

#include "aeten/lang/interface.h"
