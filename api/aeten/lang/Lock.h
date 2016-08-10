#include <stdbool.h>
//#include "TimeUnit.h"


#include "aeten/lang/start-interface.h"
#define AETEN_LANG_INTERFACE \
	aeten_lang__interface(Lock)

#define AETEN_LANG_METHODS \
    aeten_lang__method(void, lock); \
    aeten_lang__method(void, unlock); \
//	aeten_lang__method(bool, tryLock, unsigned long /* time */, TimeUnit* /* unit */);

#ifndef _AETEN_LANG_LOCK_H
	#define _AETEN_LANG_LOCK_H
	#include "aeten/lang/end-interface.h"
#endif
