#include <stdio.h>

#include "aeten/lang/import.h"
#include "aeten/lang/CopyOnWriteArrayList.h"

void print_methods(interface_t *interface, int level) {
	unsigned int i, mtd_i, arg_i, mtd_size, sign_size;
	type_t *type;
	mtd_size = call(interface->methods, size);
	for (mtd_i=0; mtd_i<mtd_size; ++mtd_i) {
		method_definition_t *method = call(interface->methods, get, mtd_i);
		printf("\n");
		for (i=0; i<level+1; ++i) printf("\t");
		printf("%s (", method->name);
		sign_size = call(method->signature, size);
		for (arg_i=1; arg_i<sign_size; ++arg_i) {
			type = call(method->signature, get, arg_i);
			printf("%s%s /%u/", (arg_i==1)? "": ", ", type->name, type->size);
		}
		type = call(method->signature, get, 0);
		printf("): %s /%u/", type->name, type->size);
	}
}

void print_parents(aeten_lang__interface_t *interface, int level) {
	int i;
	for (i=0; i<level; ++i) printf("\t");
	printf("%s(%x) {", interface->name, interface);
	print_methods(interface, level);
	printf("\n");
	for (i=0; i<call(interface->parents, size); ++i) {
		print_parents(call(interface->parents, get, i), level+1);
	}
	for (i=0; i<level; ++i) printf("\t");
	printf("}\n");
}

int main(int argc, char **argv) {
	int i, value;
	List *list = new_instance(CopyOnWriteArrayList, sizeof(int), 5);
	for (i=0; i<10; ++i) {
		list->add(list, (void*)&i);
	}
	for (i=0; i<list->size(list); ++i) {
		value = *((int*) list->get(list, i));
		AETEN_DEBUG_ASSERT(value==i);
		printf("Value of list[%d]=%d\n", i, value);
	}
	print_parents(list->_header.interface, 0);
	delete(list);
	return 0;
}
