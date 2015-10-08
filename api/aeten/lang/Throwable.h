#include <signal.h>
#include "aeten/lang/Closable.h"

#include "aeten/lang/start-interface.h"
#define AETEN_LANG_INTERFACE \
	aeten_lang__interface(aeten_lang__Throwable)

#define AETEN_LANG_METHODS \
	aeten_lang__method(char*, message); \
	aeten_lang__method(void, print_message);

#ifndef _AETEN_LANG_EXCEPTION_H
#define _AETEN_LANG_EXCEPTION_H
#include "aeten/lang/end-interface.h"

typedef void   (*aeten_lang__try_t)   (void);
typedef void   (*aeten_lang__catch_t) (aeten_lang__Throwable* exception);
typedef void   (*aeten_lang__finally_t)   (void);
typedef struct aeten_lang__handles_exception_st {
	char* exception;
	aeten_lang__catch_t catch_block;
} aeten_lang__handled_exception_t;

aeten_lang__Throwable* aeten_lang__Throwable__get_thrown(void);
void aeten_lang__Throwable__handle(aeten_lang__handled_exception_t* handled_exception);
void aeten_lang__Throwable__throw(aeten_lang__Throwable*);
void aeten_lang__Throwable__reset(void);



/**
 * Start a try block whith potentially aeten_lang__Closable resources.
 * Needs aeten/lang/ArrayList.h inclusion
 */
#define aeten_lang__try(...) { \
	__label__ _finally_;\
	unsigned int _handled_exception_index_ = 0; \
	unsigned int _try_resource_; \
	int _catched_ = 0; \
	aeten_lang__try_t _try_block_; \
	aeten_lang__catch_t _catch_block_; \
	aeten_lang__List* _handled_exceptions_ = aeten_lang__ArrayList__new(sizeof(aeten_lang__handled_exception_t), 1); \
	aeten_lang__handled_exception_t* _handled_exception_ref_ = NULL; \
	aeten_lang__Throwable__reset(); \
	aeten_lang__Closable* _try_resources_[] = { __VA_ARGS__ } ; \
	size_t _try_resources_size_ = AETEN_FOR_EACH_NARG(__VA_ARGS__); \
	void _finally_block_ (void) { \
		for (_try_resource_=0; _try_resource_<_try_resources_size_; ++_try_resource_) { \
			if(_try_resources_[_try_resource_]!=NULL) _try_resources_[_try_resource_]->close(_try_resources_[_try_resource_]); \
		} \
		if (!_catched_ && aeten_lang__Throwable__get_thrown()) { \
			aeten_lang__Throwable* _error_ = aeten_lang__Throwable__get_thrown(); \
			_error_->print_message(_error_); \
			raise(SIGABRT); \
		} ;\
		aeten_lang__Throwable__reset(); \
	} \
	{ \
		_try_block_ = ({ void _aeten_lang__block_ (void)

#define aeten_lang__catch(exception_interface, _exception_) \
			_aeten_lang__block_; \
		}); \
		if (_handled_exception_ref_) { \
			_handled_exception_ref_->catch_block = (aeten_lang__catch_t)({ \
				void _aeten_lang__block_ (aeten_lang__Throwable* exception) { \
					_catch_block_(exception); \
					_catched_ = 1; \
					goto _finally_; \
				} _aeten_lang__block_; \
			});\
		} \
	} \
	{ \
		aeten_lang__handled_exception_t _handled_exception_; \
		_handled_exceptions_->add(_handled_exceptions_, &_handled_exception_); \
		_handled_exception_ref_ = _handled_exceptions_->get(_handled_exceptions_, _handled_exception_index_++); \
		aeten_lang__Throwable__handle(_handled_exception_ref_); \
		_handled_exception_ref_->exception = #exception_interface; \
		_catch_block_ =  (aeten_lang__catch_t)({ \
			void _aeten_lang__block_ (exception_interface* exception) \

#define aeten_lang__finally(finally_block) \
			_aeten_lang__block_; \
		}); \
		_handled_exception_ref_->catch_block = (aeten_lang__catch_t)({ \
			void _aeten_lang__block_ (aeten_lang__Throwable* exception) { \
				_catch_block_(exception); \
				_catched_ = 1; \
				goto _finally_; \
			} _aeten_lang__block_; \
		});\
	} \
	_try_block_(); \
	_finally_: _finally_block_(); \
	finally_block; \
}


/** Check expression or throws exception (TODO) */
// TODO: goto aeten_lang__catch__##exception;
#define aeten_lang__check(expression, exception, message_format, ...) \
	do { \
		if (!(expression)) { \
			char* message = aeten_lang__string_from_format(message_format, ##__VA_ARGS__); \
			char* prefixed_message = aeten_lang__string_from_format("%s +%u: Check (%s): %s (%s)", __func__, __LINE__, #expression, #exception, message); \
			aeten_lang__Throwable__throw(exception##__new(prefixed_message)); \
			free(message); \
			free(prefixed_message); \
		} \
	} while (0);

#endif
