
#ifndef _AETEN_LANG_H
#define _AETEN_LANG_H
#ifdef _aeten_lang_IMPORT
#include "aeten/lang/export.h"
#endif


#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "aeten/lang/String.h"
#include "aeten/lang/FOR_EACH.h"

typedef struct aeten_lang__interface_st             aeten_lang__interface_t;
typedef struct aeten_lang__class_st                 aeten_lang__class_t;
typedef struct aeten_lang__method_definition_st     aeten_lang__method_definition_t;
typedef struct aeten_lang__method_implementation_st aeten_lang__method_implementation_t;
typedef struct aeten_lang__type_st                  aeten_lang__type_t;
typedef struct aeten_lang__object_header_st         aeten_lang__object_header_t;
typedef struct aeten_lang__Signature_st             aeten_lang__Signature;
typedef struct aeten_lang__MethodsList_st           aeten_lang__MethodsList;
typedef struct aeten_lang__ParentsList_st           aeten_lang__ParentsList;
typedef struct aeten_lang__array_st                 aeten_lang__array_t;


typedef void   (*aeten_lang__initializer_t) (aeten_lang__interface_t*);
typedef void   (*aeten_lang__finalizer_t)   (aeten_lang__interface_t*);


struct aeten_lang__type_st {
	char const *name;
	size_t size;
};

struct aeten_lang__array_st {
	size_t length;
	size_t element_size;
	void*  elements;
};

struct aeten_lang__interface_st {
	char const *name;
	aeten_lang__MethodsList* methods;
	aeten_lang__ParentsList* parents;
};


#define _aeten_lang__object_header \
	char*                     _interface; \
	aeten_lang__initializer_t _initialize; \
	aeten_lang__finalizer_t   _finalize

struct aeten_lang__object_header_st {
	_aeten_lang__object_header;
};

#define _aeten_lang__InterfaceList \
	_aeten_lang__object_header; \
	size_t (*size)(/*aeten_lang__List*/void*)

struct aeten_lang__Signature_st {
	_aeten_lang__InterfaceList;
	aeten_lang__type_t*  (*get) (aeten_lang__Signature*, unsigned int);
};

struct aeten_lang__MethodsList_st {
	_aeten_lang__InterfaceList;
	aeten_lang__method_definition_t*  (*get) (aeten_lang__MethodsList*, unsigned int);
};

struct aeten_lang__ParentsList_st {
	_aeten_lang__InterfaceList;
	aeten_lang__interface_t*  (*get) (aeten_lang__ParentsList*, unsigned int);
};


struct aeten_lang__method_definition_st {
	aeten_lang__interface_t const *interface;
	char const * name;
	aeten_lang__Signature *signature;
};

struct aeten_lang__method_implementation_st {
	aeten_lang__method_definition_t *definition;
	void *implementation;
};

void _aeten_lang__construct(aeten_lang__interface_t *iface, char const *iface_name, aeten_lang__interface_t *ifc_list[]);
char *_aeten_lang__join_strings(char *dest, char* src[], char join);
void _aeten_lang__method_construct(aeten_lang__interface_t *iface, char const *name, char *signature_types[], size_t signature_sizes[]);
aeten_lang__interface_t* aeten_lang__get_interface(const char* iface_name);


#define AETEN_COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#ifdef AETEN_DEBUG
#	include<stdio.h>
#	include <assert.h>
#	undef AETEN_DEBUG
static char* _aeten_debug_tmp_str = 0;
#	define AETEN_DEBUG(format, ...) do { \
		fprintf(stderr, "%s +%d: " format "\n", __FILE__, __LINE__, __VA_ARGS__); \
		if (_aeten_debug_tmp_str) { \
			free(_aeten_debug_tmp_str); \
			_aeten_debug_tmp_str = 0; \
		} \
	} while (0)
#	define AETEN_DEBUG_JOIN_STRINGS(src, join) _aeten_lang__join_strings(_aeten_debug_tmp_str, src, join)
#	define AETEN_DEBUG_ASSERT(...) assert(__VA_ARGS__)

#else
#	define AETEN_DEBUG(...)
#	define AETEN_DEBUG_JOIN_STRINGS(dest, src)
#	define AETEN_DEBUG_ASSERT(...)
#endif

#if defined(__GNUC__)
#	define aeten_lang__static_constructor(fn) \
	static void fn(void) __attribute__((constructor)); \
	static void fn(void)
#elif defined(_MSC_VER)
#	define aeten_lang__static_constructor(fn) \
	static void __cdecl fn(void); \
	__declspec(allocate(".CRT$XCU")) void (__cdecl *fn##_)(void) = fn; \
	static void __cdecl fn(void)
#endif

#if defined(aeten_lang__static_constructor) && !defined(_aeten_lang__destructor)
#	define _aeten_lang__destructor(fn) \
	static void fn(void);\
	aeten_lang__static_constructor(_aeten_lang__destructor_##fn) { \
		atexit( fn ); \
	} \
	static void fn(void)
#endif

#define aeten_lang__type_of(a) \
	((aeten_lang__type_t) { #a, sizeof(a) })

#define aeten_lang__init(iface, ...) \
	iface AETEN_FIRST_ARG(__VA_ARGS__); \
	iface##__init(&__VA_ARGS__);

#define aeten_lang__delete(object) do { \
		object->_finalize((aeten_lang__interface_t*)object); \
		free(object); \
	} while(0)


#define aeten_lang__call(object_ref, method, ...) \
	object_ref->method(object_ref, ##__VA_ARGS__)

#define aeten_lang__cnc aeten_lang__cast_and_call
#define aeten_lang__cast_and_call(object_ref, type, method, ...) ({ \
	type * ref = aeten_lang__cast_ref(type, object_ref); \
	ref->method(ref, ##__VA_ARGS__); \
})

/** Start a try block whith potentially aeten_lang__Closable resources */
#define aeten_lang__try(...) { \
	__label__ _finally_;\
	unsigned int _handled_exception_index_ = 0; \
	unsigned int _try_resource_; \
	int _catched_ = 0; \
	aeten_lang__try_t _try_block_; \
	aeten_lang__catch_t _catch_block_; \
	aeten_lang__List* _handled_exceptions_ = aeten_lang__ArrayList__new(sizeof(aeten_lang__handled_exception_t), 1); \
	aeten_lang__handled_exception_t* _handled_exception_ref_ = NULL; \
	aeten_lang__Exception__reset(); \
	aeten_lang__Closable* _try_resources_[] = { __VA_ARGS__ } ; \
	size_t _try_resources_size_ = AETEN_FOR_EACH_NARG(__VA_ARGS__); \
	void _finally_block_ () { \
		for (_try_resource_=0; _try_resource_<_try_resources_size_; ++_try_resource_) { \
			if(_try_resources_[_try_resource_]!=NULL) _try_resources_[_try_resource_]->close(_try_resources_[_try_resource_]); \
		} \
		if (!_catched_ && aeten_lang__Exception__get_thrown()) { \
			aeten_lang__Exception* _error_ = aeten_lang__Exception__get_thrown(); \
			_error_->print_message(_error_); \
			raise(SIGABRT); \
		} ;\
		aeten_lang__Exception__reset(); \
	} \
	{ \
		_try_block_ = ({ void _aeten_lang__block_ ()

#define aeten_lang__catch(exception_interface, _exception_) \
			_aeten_lang__block_; \
		}); \
		if (_handled_exception_ref_) { \
			_handled_exception_ref_->catch_block = (aeten_lang__catch_t)({ \
				void _aeten_lang__block_ (aeten_lang__Exception* exception) { \
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
		aeten_lang__Exception__handle(_handled_exception_ref_); \
		_handled_exception_ref_->exception = #exception_interface; \
		_catch_block_ =  (aeten_lang__catch_t)({ \
			void _aeten_lang__block_ (exception_interface* exception) \

#define aeten_lang__finally(finally_block) \
			_aeten_lang__block_; \
		}); \
		_handled_exception_ref_->catch_block = (aeten_lang__catch_t)({ \
			void _aeten_lang__block_ (aeten_lang__Exception* exception) { \
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
			aeten_lang__Exception__throw(exception##__new(prefixed_message)); \
			free(message); \
			free(prefixed_message); \
		} \
	} while (0);


// TODO: check instance interfaces before
#define aeten_lang__cast_ref(type, object_ref) ((type*) object_ref)


#define _AETEN_REF_OF_EACH_IFACE(iface) &_##iface##_i,
// TODO: fill Interface structure with methods
// TODO: Get rid of multiple constructor call (move {con,de}structor declaration into c files)
#define _aeten_lang__define_type(iface, ...) \
	typedef struct _##iface##_st iface; \
	aeten_lang__interface_t _##iface##_i; \
	aeten_lang__static_constructor(_##iface##_c) { \
		_aeten_lang__construct(&_##iface##_i, #iface, (aeten_lang__interface_t*[]) { \
			AETEN_FOR_EACH(_AETEN_REF_OF_EACH_IFACE, ##__VA_ARGS__) (aeten_lang__interface_t*)NULL \
		}); \
	} \
	_aeten_lang__destructor(_##iface##_d) { \
		aeten_lang__delete(_##iface##_i.methods); \
	}

void _aeten_lang__init();
aeten_lang__static_constructor(_aeten_lang__interfaces_c) {
	_aeten_lang__init();
}

#endif // AETEN_LANG_H
