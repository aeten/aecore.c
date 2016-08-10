#include <pthread.h>

#ifndef _AETEN_LANG_PTRLOCK_H
#define _AETEN_LANG_PTRLOCK_H

#define AETEN_LANG_IMPLEMENTATION_H \
	aeten_lang__implementation(PThreadReadLock, Lock)

#define AETEN_LANG_PRIVATE \
	aeten_lang__private(pthread_rwlock_t* rw_lock)

#define AETEN_LANG_CONSTRUCTORS \
	aeten_lang__constructor(pthread_rwlock_t* /*rw_lock*/)

#include "aeten/lang/Lock.h"
#include "aeten/lang/implementation.h"

#endif

