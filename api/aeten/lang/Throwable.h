#include <signal.h>
#include "aeten/lang/Closable.h"
#undef AETEN_LANG_INTERFACE
#undef AETEN_LANG_METHODS

#define AETEN_LANG_INTERFACE \
	aeten_lang__interface(aeten_lang__Throwable)

#define AETEN_LANG_METHODS \
	aeten_lang__method(char*, message); \
	aeten_lang__method(void, print_message);

#ifndef _AETEN_LANG_EXCEPTION_H
#define _AETEN_LANG_EXCEPTION_H

#include "aeten/lang/interface.h"

typedef void   (*aeten_lang__try_t)   ();
typedef void   (*aeten_lang__catch_t) (aeten_lang__Throwable* exception);
typedef void   (*aeten_lang__finally_t)   ();
typedef struct aeten_lang__handles_exception_st {
	char* exception;
	aeten_lang__catch_t catch_block;
} aeten_lang__handled_exception_t;

aeten_lang__Throwable* aeten_lang__Throwable__get_thrown();
void aeten_lang__Throwable__handle(aeten_lang__handled_exception_t* handled_exception);
void aeten_lang__Throwable__throw(aeten_lang__Throwable*);
void aeten_lang__Throwable__reset();

#endif
