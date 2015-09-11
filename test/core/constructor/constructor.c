#include "aeten/core/constructor.h"
#include <stdio.h>

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
