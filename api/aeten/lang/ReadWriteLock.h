#include <stdbool.h>
#include "aeten/lang/Lock.h"

#include "aeten/lang/start-interface.h"
#define AETEN_LANG_INTERFACE \
	aeten_lang__interface(ReadWriteLock)

#define AETEN_LANG_METHODS \
	aeten_lang__method(Lock*, read_lock); \
	aeten_lang__method(Lock*, write_lock);

#ifndef _AETEN_LANG_RWLOCK_H
	#define _AETEN_LANG_RWLOCK_H
	#include "aeten/lang/end-interface.h"
#endif
