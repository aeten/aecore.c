#include "aeten/core.h"
#include <stdio.h>

interface(List)
method(List, size_t, size)
method(List, int, foo)

impl(ArrayList, &List) {
	_aeten_core__object__impl
	size_t size;
	void *array;
};

ArrayList * ArrayList__init(ArrayList *list, void *array, size_t size) {
	_aeten_core__object__new(ArrayList, list);
	list->array = array;
	list->size = size;
	return list;
}
void ArrayList__delete(ArrayList *list) {
	free(list);
}
ArrayList * ArrayList__new(size_t nmemb, size_t size) {
	ArrayList *list = (ArrayList *) calloc(1, sizeof(ArrayList) + (nmemb*size));
	return ArrayList__init(list, (void*)(list+sizeof(ArrayList)), nmemb);
}

interface(Map)
method(Map, size_t, size)

impl(Table, &Map) {
	_aeten_core__object__impl
	size_t size;
};
Table * Table__init(Table *map) {
	_aeten_core__object__new(Table, map);
	return map;
}
Table * Table__new() {
	Table *map = (Table *) calloc(1, sizeof(Table));
	return Table__init(map);
}


void print_methods(aeten_interface *interface) {
	int i;
	printf(" (");
	for (i=0; interface->methods[i]; ++i) {
		printf("%s%s", ((i==0)? "": ", "), interface->methods[i]->name);
	}
	printf(") ");
}
void print_parents(aeten_interface *interface) {
	int i;
	print_methods(interface);
	for (i=0; interface->parents[i]; ++i) {
		printf("%s%s", ((i==0)? "": ", "), interface->parents[i]->name);
		print_parents(interface->parents[i]);
	}
}

int main(int argc, char **argv) {
	Table map;
	Table__init(&map);
	ArrayList list = *ArrayList__new(10, sizeof(int));

	printf("%s:", map.interface->name);
	print_parents(map.interface);
	printf("\n");

	printf("%s:", list.interface->name);
	print_parents(list.interface);
	printf("\n");
	return 0;
}
