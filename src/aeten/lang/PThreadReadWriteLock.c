#include "aeten/lang/Throwable.h"
#include "aeten/lang/RuntimeError.h"

#include "aeten/lang/PThreadReadLock.h"
#include "aeten/lang/PThreadWriteLock.h"

#define AETEN_LANG_IMPLEMENTATION_C
#include "aeten/lang/PThreadReadWriteLock.h"


inline void PThreadReadWriteLock__initialize(PThreadReadWriteLock *rwlock) {
	pthread_rwlock_t pthread_rwlock = PTHREAD_RWLOCK_INITIALIZER;
	rwlock->_private.rw_lock = pthread_rwlock;
	rwlock->_private.read_lock = PThreadReadLock__new(&rwlock->_private.rw_lock);
	rwlock->_private.write_lock = PThreadWriteLock__new(&rwlock->_private.rw_lock);
}

inline void PThreadReadWriteLock__finalize(PThreadReadWriteLock *rwlock) {
	delete(rwlock->_private.read_lock);
	delete(rwlock->_private.write_lock);
	pthread_rwlock_destroy(&rwlock->_private.rw_lock);
}

inline Lock* PThreadReadWriteLock__read_lock(PThreadReadWriteLock *rwlock) {
	return rwlock->_private.read_lock;
}

inline Lock* PThreadReadWriteLock__write_lock(PThreadReadWriteLock *rwlock) {
	return rwlock->_private.write_lock;
}


