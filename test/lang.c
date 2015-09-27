#include <stdio.h>

#include "aeten/lang/import.h"
#include "aeten/lang/ArrayList.h"

void print_methods(aeten_lang__interface_t *interface) {
	int i, a;
	printf(" (");
	for (i=0; interface->methods[i].name; ++i) {
		printf("%s%s (", ((i==0)? "": ", "), interface->methods[i].name);
		for (a=1; interface->methods[i].signature[a].name; ++a) {
			printf("%s%s(%u)", ((a==0)? "": ", "), interface->methods[i].signature[a].name, interface->methods[i].signature[a].size);
		}
		printf("): %s", interface->methods[i].signature[0].name);
	}
	printf(") ");
}
void print_parents(aeten_lang__interface_t *interface) {
	int i;
	print_methods(interface);
	for (i=0; interface->parents[i]; ++i) {
		printf("%s%s", ((i==0)? "": ", "), interface->parents[i]->name);
		print_parents(interface->parents[i]);
	}
}

int main(int argc, char **argv) {
	int i, value;
	ArrayList *list = new(ArrayList, sizeof(int), 10);
	for (i=0; i<list->length; ++i) {
		ArrayList__set(list, i, (void*)&i);
	}
	for (i=0; i<list->length; ++i) {
		value = *((int*) ArrayList__get(list, i));
		AETEN_DEBUG_ASSERT(value==i);
		printf("Value of list[%d]=%d\n", i, value);
	}
	printf("%s:", list->interface->name);
	print_parents(list->interface);
	printf("\n");
	delete(list);

	return 0;
}
