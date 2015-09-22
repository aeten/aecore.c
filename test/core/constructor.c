#include "aeten/core.h"
#include <stdio.h>

#define constructor(fn) aeten_core_constructor(fn)
#define destructor(fn) aeten_core_destructor(fn)


constructor(start) {
    printf("%s\n", __func__);
}

destructor(end) {
    printf("%s\n", __func__);
}

int main(int argc, char * argv[]) {
	printf("%s\n", __func__);
	return 0;
}
