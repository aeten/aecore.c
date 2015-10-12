#include "aeten/lang/Throwable.h"
#include "aeten/lang/ArrayList.h"

/* TODO: Use a Stack when will be implemented */
__thread Throwable* _aeten_lang__thrown_exception = NULL;
__thread List* _aeten_lang__handled_exceptions = NULL;

Throwable* Throwable__get_thrown(void) {
	return _aeten_lang__thrown_exception;
}

void Throwable__handle(aeten_lang__handled_exception_t* handled_exception) {
	_aeten_lang__handled_exceptions->add(_aeten_lang__handled_exceptions, &handled_exception); \
}

void Throwable__throw(Throwable* exception) {
	unsigned int i;
	_aeten_lang__thrown_exception = exception;
	for (i=0; i<_aeten_lang__handled_exceptions->size(_aeten_lang__handled_exceptions); ++i) {
		aeten_lang__handled_exception_t* handled_exception = *(aeten_lang__handled_exception_t**)_aeten_lang__handled_exceptions->get(_aeten_lang__handled_exceptions, i);
		if (0 == strcmp(handled_exception->exception, _aeten_lang__thrown_exception->_implementation->interface)) {
			handled_exception->catch_block(exception);
		}
	}
}

void  Throwable__reset(void) {
	_aeten_lang__thrown_exception = NULL;
	if (_aeten_lang__handled_exceptions != NULL) {
		delete(_aeten_lang__handled_exceptions);
	}
	_aeten_lang__handled_exceptions = ArrayList__new(sizeof(aeten_lang__handled_exception_t*), 1);
}
