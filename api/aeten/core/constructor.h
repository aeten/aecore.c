#include <stdlib.h>

#if defined(__cplusplus)
	struct construct { construct(void (*f)(void)) { f(); } };
#	define constructor(fn) \
		static void fn(void); \
		static construct constructor_##fn(fn); \
		void fn()

#else
#	if defined(__GNUC__)
#		define constructor(fn) \
			static void fn(void) __attribute__((constructor)); \
			static void fn(void)

#	elif defined(_MSC_VER)
#		define constructor(fn) \
			static void __cdecl fn(void); \
			__declspec(allocate(".CRT$XCU")) void (__cdecl *fn##_)(void) = fn; \
			static void __cdecl fn(void)
#	endif
#endif

#if defined(constructor) && !defined(destructor)
#	define destructor(fn) \
		static void fn(void);\
		constructor(destructor_##fn) { \
			atexit( fn ); \
		} \
		static void fn(void)
#endif

