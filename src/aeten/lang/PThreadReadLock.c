#include "aeten/lang/RuntimeError.h"

#define AETEN_LANG_IMPLEMENTATION_C
#include "aeten/lang/PThreadReadLock.h"

inline void PThreadReadLock__initialize(PThreadReadLock *lock, pthread_rwlock_t* rw_lock) {
	lock->_private.rw_lock = rw_lock;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
inline void PThreadReadLock__finalize(PThreadReadLock *lock) {
}
#pragma GCC diagnostic pop

inline void PThreadReadLock__lock(PThreadReadLock *lock) {
	check(pthread_rwlock_rdlock(lock->_private.rw_lock) == 0, RuntimeError, "pthread_rwlock_wrlock");
}

inline void PThreadReadLock__unlock(PThreadReadLock *lock) {
	check(pthread_rwlock_unlock(lock->_private.rw_lock) == 0, RuntimeError, "pthread_rwlock_wrlock");
}

