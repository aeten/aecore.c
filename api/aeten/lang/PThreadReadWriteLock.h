#ifndef _AETEN_LANG_PTRWLOCK_H
#define _AETEN_LANG_PTRWLOCK_H

#include <pthread.h>

#define AETEN_LANG_IMPLEMENTATION_H \
	aeten_lang__implementation(PThreadReadWriteLock, ReadWriteLock)

#define AETEN_LANG_PRIVATE \
	aeten_lang__private(pthread_rwlock_t rw_lock, Lock* read_lock, Lock* write_lock)

#define AETEN_LANG_CONSTRUCTORS \
	aeten_lang__constructor()

#include "aeten/lang/ReadWriteLock.h"
#include "aeten/lang/implementation.h"

#endif
