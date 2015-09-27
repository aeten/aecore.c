#include "aeten/lang/import.h"
#include <stdio.h>

interface(List);
method(List, size_t, size);
//method(List, void, set, int, void);
method(List, void*, get, int);

implementation(ArrayList, List) {
	_aeten_lang__object__impl
	size_t length;
	size_t element_size;
	void *elements;
};

ArrayList * ArrayList__init(ArrayList *list, size_t element_size, size_t length);
ArrayList * ArrayList__new(size_t element_size, size_t length);
void ArrayList__finalize(ArrayList *list);
void * ArrayList__get(ArrayList *list, int index);
void ArrayList__set(ArrayList *list, int index, void *value);

ArrayList * ArrayList__new(size_t element_size, size_t length) {
	ArrayList *list = (ArrayList *) calloc(1, sizeof(ArrayList));
	return ArrayList__init(list, element_size, length);
}
ArrayList * ArrayList__init(ArrayList *list, size_t element_size, size_t length) {
	_aeten_lang__object__new(ArrayList, list);
	list->elements = calloc(length, element_size);
	list->length = length;
	list->element_size = element_size;
	return list;
}
void ArrayList__finalize(ArrayList *list) {
	free(list->elements);
}
void ArrayList__set(ArrayList *list, int index, void *value) {
	unsigned long pointer = (unsigned long)list->elements;
	pointer += index*list->element_size;
	memcpy((void*)pointer, value, list->element_size);
}
void * ArrayList__get(ArrayList *list, int index) {
	unsigned long pointer = (unsigned long)list->elements;
	pointer += index*list->element_size;
	return (void*) pointer;
}
size_t ArrayList__size(ArrayList *list) {
	list->length;
}

void print_methods(aeten_lang__interface_t *interface) {
	int i, a;
	printf(" (");
	for (i=0; interface->methods[i].name; ++i) {
		printf("%s%s (", ((i==0)? "": ", "), interface->methods[i].name);
		//for (a=0; interface->methods[i].args_type && interface->methods[i].args_type[a].name; ++a) {
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
		assert(value==i);
		printf("Value of list[%d]=%d\n", i, value);
	}
	printf("%s:", list->interface->name);
	print_parents(list->interface);
	printf("\n");
	delete(list);

	return 0;
}
