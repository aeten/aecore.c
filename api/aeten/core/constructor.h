#include <stdlib.h>

#if defined(__cplusplus)
	struct aeten_core_construct { aeten_core_construct(void (*f)(void)) { f(); } };
#	define aeten_core_constructor(fn) \
		static void fn(void); \
		static aeten_core_construct aeten_core_constructor_##fn(fn); \
		void fn()

#else
#	if defined(__GNUC__)
#		define aeten_core_constructor(fn) \
			static void fn(void) __attribute__((constructor)); \
			static void fn(void)

#	elif defined(_MSC_VER)
#		define aeten_core_constructor(fn) \
			static void __cdecl fn(void); \
			__declspec(allocate(".CRT$XCU")) void (__cdecl *fn##_)(void) = fn; \
			static void __cdecl fn(void)
#	endif
#endif

#if defined(aeten_core_constructor) && !defined(aeten_core_destructor)
#	define aeten_core_destructor(fn) \
		static void fn(void);\
		aeten_core_constructor(aeten_core_destructor_##fn) { \
			atexit( fn ); \
		} \
		static void fn(void)
#endif

