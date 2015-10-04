#pragma once

#define AETEN_LANG_INTERFACE \
	aeten_lang__interface(aeten_lang__Exception)

#define AETEN_LANG_METHODS \
	aeten_lang__method(char*, message); \
	aeten_lang__method(void, print_message);


#include "aeten/lang/interface.h"
