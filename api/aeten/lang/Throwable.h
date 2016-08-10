#include <signal.h>

#define AETEN_LANG_REQUIRE
#include "aeten/lang/Closable.h"

#include "aeten/lang/start-interface.h"
#define AETEN_LANG_INTERFACE \
	aeten_lang__interface(Throwable)

#define AETEN_LANG_METHODS \
	aeten_lang__method(char*, message); \
	aeten_lang__method(void, print_message);

#ifndef _AETEN_LANG_THROWABLE_H
	#define _AETEN_LANG_THROWABLE_H
	#include "aeten/lang/end-interface.h"

typedef void   (*aeten_lang__try_t)   (void);
typedef void   (*aeten_lang__catch_t) (Throwable* exception);
typedef void   (*aeten_lang__finally_t)   (void);
typedef struct _aeten_lang__handles_exception_st {
	char* exception;
	aeten_lang__catch_t catch_block;
} aeten_lang__handled_exception_t;

Throwable* Throwable__get_thrown(void);
aeten_lang__handled_exception_t* Throwable__handle(void);
void Throwable__throw(Throwable* exception);
void Throwable__set_finally(aeten_lang__finally_t finally_block);
void Throwable__reset(void);


/**
 * Start a try block whith potentially Closable resources.
 * Needs aeten/lang/ArrayList.h inclusion
 */
#define try(...) { \
	__label__ _finally_;\
	unsigned int _try_resource_; \
	int _catched_ = 0; \
	aeten_lang__try_t _try_block_; \
	aeten_lang__catch_t _catch_block_; \
	Throwable__reset(); \
	aeten_lang__handled_exception_t* _handled_exception_ = NULL; \
	Closable* _try_resources_[] = { __VA_ARGS__ } ; \
	size_t _try_resources_size_ = AETEN_FOR_EACH_NARG(__VA_ARGS__); \
	void _finally_block_ (void) { \
		for (_try_resource_=0; _try_resource_<_try_resources_size_; ++_try_resource_) { \
			if(_try_resources_[_try_resource_]!=NULL) _try_resources_[_try_resource_]->close(_try_resources_[_try_resource_]); \
		} \
		if (!_catched_ && Throwable__get_thrown()) { \
			Throwable* _error_ = Throwable__get_thrown(); \
			_error_->print_message(_error_); \
			raise(SIGABRT); \
		} \
		Throwable__reset(); \
	} \
	{ \
		_try_block_ = ({ void _aeten_lang__block_ (void)

#define catch(exception_interface, _exception_) \
			_aeten_lang__block_; \
		}); \
		if (_handled_exception_) { \
			_handled_exception_->catch_block = (aeten_lang__catch_t)({ \
				void _aeten_lang__block_ (Throwable* exception) { \
					_catch_block_(exception); \
					_catched_ = 1; \
					goto _finally_; \
				} _aeten_lang__block_; \
			});\
		} \
	} \
	{ \
		_handled_exception_ = Throwable__handle(); \
		_handled_exception_->exception = #exception_interface; \
		_catch_block_ =  (aeten_lang__catch_t)({ \
			void _aeten_lang__block_ (Throwable* exception) \

#define finally(finally_block) \
			_aeten_lang__block_; \
		}); \
		Throwable__set_finally(({void _goto_finally_(void) {finally_block;goto _finally_;} _goto_finally_;})); \
		_handled_exception_->catch_block = (aeten_lang__catch_t)({ \
			void _aeten_lang__block_ (Throwable* exception) { \
				_catch_block_(exception); \
				_catched_ = 1; \
				goto _finally_; \
			} _aeten_lang__block_; \
		});\
	} \
	_try_block_(); \
	_finally_: _finally_block_(); \
}


/** Check expression or throws exception (TODO) */
#define check(expression, exception, message_format, ...) \
	do { \
		if (!(expression)) { \
			char* message = aeten_lang__string_from_format(message_format, ##__VA_ARGS__); \
			char* prefixed_message = aeten_lang__string_from_format("%s +%u: Check (%s): %s (%s)", __func__, __LINE__, #expression, #exception, message); \
			Throwable__throw(exception##__new(prefixed_message)); \
			free(message); /* TODO: move it into finally block */ \
			free(prefixed_message); /* TODO: move it into finally block */ \
		} \
	} while (0);

#endif
