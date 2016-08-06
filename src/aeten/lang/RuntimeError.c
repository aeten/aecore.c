#define AETEN_LANG_IMPLEMENTATION_C
#include "aeten/lang/RuntimeError.h"

#include <stdio.h>

inline void RuntimeError__initialize(RuntimeError *exception, char* message) {
	exception->_private.message = (char*)malloc(strlen(message)+1);
	strcpy(exception->_private.message, message);
}

inline void RuntimeError__finalize(RuntimeError *exception) {
	free(exception->_private.message);
}

inline char* RuntimeError__message(RuntimeError *exception) {
	return exception->_private.message;
}

inline void RuntimeError__print_message(RuntimeError *exception) {
	fprintf(stderr, "%s\n", exception->_private.message);
}
