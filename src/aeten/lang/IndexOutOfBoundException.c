#define AETEN_LANG_IMPLEMENTATION_C
#include "aeten/lang/IndexOutOfBoundException.h"

#include <stdio.h>

aeten_lang__Exception * aeten_lang__IndexOutOfBoundException__initialize(aeten_lang__IndexOutOfBoundException *exception, char* message) {
	_aeten_lang__IndexOutOfBoundException__init(exception);
	exception->_private.message = (char*)malloc(strlen(message)+1);
	strcpy(exception->_private.message, message);
	return aeten_lang__cast_ref(aeten_lang__Exception, exception);
}

void aeten_lang__IndexOutOfBoundException__finalize(aeten_lang__IndexOutOfBoundException *exception) {
	free(exception->_private.message);
}

char* aeten_lang__IndexOutOfBoundException__message(aeten_lang__Exception *exception) {
	return aeten_lang__cast_ref(aeten_lang__IndexOutOfBoundException, exception)->_private.message;
}

void aeten_lang__IndexOutOfBoundException__print_message(aeten_lang__Exception *exception) {
	fprintf(stderr, "%s\n", aeten_lang__cast_ref(aeten_lang__IndexOutOfBoundException, exception)->_private.message);
}
