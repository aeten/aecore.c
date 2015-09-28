#include <stdio.h>

#include "aeten/lang/import.h"
#include "aeten/lang/CopyOnWriteArrayList.h"

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
	aeten_lang__List *list = new(aeten_lang__CopyOnWriteArrayList, sizeof(int), 5);
	for (i=0; i<10; ++i) {
		list->add(list, (void*)&i);
	}
	for (i=0; i<list->size(list); ++i) {
		value = *((int*) list->get(list, i));
		AETEN_DEBUG_ASSERT(value==i);
		printf("Value of list[%d]=%d\n", i, value);
	}
	printf("%s:", list->interface->name);
	print_parents(list->interface);
	printf("\n");
	delete(list);

	return 0;
}
