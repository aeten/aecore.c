#include <stdio.h>
#include <assert.h>
#include "aeten/lang/ArrayList.h"
#include "aeten/lang/CopyOnWriteArrayList.h"
#include "aeten/lang/Throwable.h"
#include "aeten/lang/IndexOutOfBoundException.h"


void print_methods(aeten_lang__interface_t* interface, unsigned int level);
void print_parents(aeten_lang__interface_t* interface, unsigned int level);

void print_methods(aeten_lang__interface_t* interface, unsigned int level) {
	unsigned int i, mtd_i, arg_i, mtd_size, sign_size;
	aeten_lang__type_t *type;
	mtd_size = call(interface->methods, size);
	for (mtd_i=0; mtd_i<mtd_size; ++mtd_i) {
		aeten_lang__method_definition_t *method = call(interface->methods, get, mtd_i);
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

void print_parents(aeten_lang__interface_t* interface, unsigned int level) {
	unsigned int i;
	for (i=0; i<level; ++i) printf("\t");
	printf("%s(%lx) {", interface->name, (unsigned long int)interface);
	print_methods(interface, level);
	printf("\n");
	for (i=0; i<call(interface->parents, size); ++i) {
		print_parents(call(interface->parents, get, i), level+1);
	}
	for (i=0; i<level; ++i) printf("\t");
	printf("}\n");
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char **argv) {
	unsigned int i, value;
	List* list = CopyOnWriteArrayList__new(sizeof(int));
	print_parents(aeten_lang__interface_of(list), 0);

	/* check cast */
	Iterable* iterable = cast(Iterable, list);
	Iterator* iterator = iterable->iterator(iterable);
	assert(iterator==NULL);

	for (i=0; i<10; ++i) {
		list->add(list, (void*)&i);
	}

	try() {
		size_t size = list->size(list);
		for (i=0; i<size; ++i) {
			value = *(int*)list->get(list, i+8);
			printf("Value of list[%d]=%d\n", i+8, value);
		}
	} catch(IndexOutOfBoundException, exception) {
		exception->print_message(exception);
	} finally(
		printf("Finally\n");
	)
	delete(list);
	return 0;
}
#pragma GCC diagnostic pop
