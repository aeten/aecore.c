#include <stdio.h>

#include "aeten/lang/CopyOnWriteArrayList.h"
#include "aeten/lang/import.h"

void print_methods(aeten_lang__interface_t *interface, int level) {
	unsigned int i, mtd_i, arg_i, mtd_size, sign_size;
	aeten_lang__type_t *type;
	mtd_size = interface->methods->size(interface->methods);
	for (mtd_i=0; mtd_i<mtd_size; ++mtd_i) {
		aeten_lang__method_definition_t *method = interface->methods->get(interface->methods, mtd_i);
		printf("\n");
		for (i=0; i<level+1; ++i) printf("\t");
		printf("%s (", method->name);
		sign_size = method->signature->size(method->signature);
		for (arg_i=1; arg_i<sign_size; ++arg_i) {
			type = method->signature->get(method->signature, arg_i);
			printf("%s%s /%u/", (arg_i==1)? "": ", ", type->name, type->size);
		}
		type = method->signature->get(method->signature, 0);
		printf("): %s /%u/", type->name, type->size);
	}
}
void print_parents(aeten_lang__interface_t *interface, int level) {
	int i;
	for (i=0; i<level; ++i) printf("\t");
	printf("%s(%x) {", interface->name, interface);
	print_methods(interface, level);
	printf("\n");
	for (i=0; i<interface->parents->size(interface->parents); ++i) {
		print_parents(interface->parents->get(interface->parents, i), level+1);
	}
	for (i=0; i<level; ++i) printf("\t");
	printf("}\n");
}

int main(int argc, char **argv) {
	int i, value;
	aeten_lang__List *list = aeten_lang__new(aeten_lang__CopyOnWriteArrayList, sizeof(int), 5);
	for (i=0; i<10; ++i) {
		list->add(list, (void*)&i);
	}
	for (i=0; i<list->size(list); ++i) {
		value = *((int*) list->get(list, i));
		AETEN_DEBUG_ASSERT(value==i);
		printf("Value of list[%d]=%d\n", i, value);
	}
	print_parents(list->interface, 0);
	delete(list);
	return 0;
}
