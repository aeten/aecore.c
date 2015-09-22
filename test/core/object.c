#include "aeten/core.h"
#include <stdio.h>

interface(List);
impl(ArrayList, List) {
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

interface(Map);
impl(Table, Map) {
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

void print_parents(aeten_core_interface *interface) {
	int i;
	aeten_core_interface *parent = interface->parent;
	for (i=0; parent->name; ++parent, ++i) {
		printf("%s%s", (i==0 || parent->parent->name)? "": ", ", parent->name);
		print_parents(parent);
	}
}

int main(int argc, char **argv) {
	Table map;
	Table__init(&map);
	printf("%s: ", map.interface.name);
	print_parents(&map.interface);
	printf("\n");
	ArrayList list = *ArrayList__new(10, sizeof(int));
	printf("%s: ", list.interface.name);
	print_parents(&list.interface);
	printf("\n");
	return 0;
}
