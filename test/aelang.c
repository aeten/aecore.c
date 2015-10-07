#include <stdio.h>
#define AETEN_LANG_MAIN
#include "aeten/lang/import.h"
#include "aeten/lang/CopyOnWriteArrayList.h"
#include "aeten/lang/ArrayList.h"
#include "aeten/lang/Throwable.h"
#include "aeten/lang/IndexOutOfBoundException.h"


void print_methods(interface_t *interface, unsigned int level);
void print_parents(const char* interface, unsigned int level);

void print_methods(interface_t *interface, unsigned int level) {
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
			printf("%s%s /%lu/", (arg_i==1)? "": ", ", type->name, type->size);
		}
		type = call(method->signature, get, 0);
		printf("): %s /%lu/", type->name, type->size);
	}
}

void print_parents(const char* interface, unsigned int level) {
	unsigned int i;
	for (i=0; i<level; ++i) printf("\t");
	interface_t* iface = aeten_lang__get_interface(interface);
	printf("%s(%lx) {", interface, (unsigned long int)iface);
	print_methods(iface, level);
	printf("\n");
	for (i=0; i<call(iface->parents, size); ++i) {
		print_parents(call(iface->parents, get, i)->name, level+1);
	}
	for (i=0; i<level; ++i) printf("\t");
	printf("}\n");
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char **argv) {
	unsigned int i, value;
//	List* list = aeten_lang__CopyOnWriteArrayList__new(sizeof(int));
	List* list = aeten_lang__ArrayList__new(sizeof(int), 5);
	for (i=0; i<10; ++i) {
		list->add(list, (void*)&i);
	}

	print_parents(list->_interface, 0);
	aeten_lang__try() {
		size_t size = list->size(list);
		for (i=0; i<size; ++i) {
			value = *(int*)list->get(list, i+8);
			printf("Value of list[%d]=%d\n", i, value);
		}
	} aeten_lang__catch(aeten_lang__IndexOutOfBoundException, exception) {
		exception->print_message((aeten_lang__Throwable*)exception);
	} aeten_lang__finally() {
		printf("Finally\n");
	}
	aeten_lang__delete(list);
	return 0;
}
#pragma GCC diagnostic pop
