#ifndef _AETEN_LANG_OOBEXCEPTION_H
#define _AETEN_LANG_OOBEXCEPTION_H

#define AETEN_LANG_IMPLEMENTATION_H \
	aeten_lang__implementation(aeten_lang__IndexOutOfBoundException, aeten_lang__Exception)

#define AETEN_LANG_PRIVATE \
	aeten_lang__private(char* message)

#define AETEN_LANG_CONSTRUCTORS \
	aeten_lang__constructor(char* /*message*/)

#include "aeten/lang/Exception.h"
#include "aeten/lang/implementation.h"

#endif
