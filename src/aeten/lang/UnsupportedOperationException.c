#define AETEN_LANG_IMPLEMENTATION_C
#include "aeten/lang/UnsupportedOperationException.h"

#include <stdio.h>

inline void UnsupportedOperationException__initialize(UnsupportedOperationException *exception, char* message) {
	exception->_private.message = (char*)malloc(strlen(message)+1);
	strcpy(exception->_private.message, message);
}

inline void UnsupportedOperationException__finalize(UnsupportedOperationException *exception) {
	free(exception->_private.message);
}

inline char* UnsupportedOperationException__message(UnsupportedOperationException *exception) {
	return exception->_private.message;
}

inline void UnsupportedOperationException__print_message(UnsupportedOperationException *exception) {
	fprintf(stderr, "%s\n", exception->_private.message);
}
