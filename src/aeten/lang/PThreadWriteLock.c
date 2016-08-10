#include "aeten/lang/RuntimeError.h"

#define AETEN_LANG_IMPLEMENTATION_C
#include "aeten/lang/PThreadWriteLock.h"

inline void PThreadWriteLock__initialize(PThreadWriteLock *lock, pthread_rwlock_t* rw_lock) {
	lock->_private.rw_lock = rw_lock;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
inline void PThreadWriteLock__finalize(PThreadWriteLock *lock) {
}
#pragma GCC diagnostic pop

inline void PThreadWriteLock__lock(PThreadWriteLock *lock) {
	check(pthread_rwlock_wrlock(lock->_private.rw_lock) == 0, RuntimeError, "pthread_rwlock_wrlock");
}

inline void PThreadWriteLock__unlock(PThreadWriteLock *lock) {
	check(pthread_rwlock_unlock(lock->_private.rw_lock) == 0, RuntimeError, "pthread_rwlock_wrlock");
}

