#ifndef AETEN_LANG_COPYONWRITEARRAYLIST_H
#define AETEN_LANG_COPYONWRITEARRAYLIST_H

#include "aeten/lang/import.h"
#include "aeten/lang/List.h"

struct aeten_lang__CopyOnWriteArrayList__private_st {
	size_t capacity;
	size_t size;
	size_t element_size;
	void *elements;
};

implementation(aeten_lang__CopyOnWriteArrayList, aeten_lang__List) {
	aeten_lang__List__header(aeten_lang__CopyOnWriteArrayList);
	aeten_lang__CopyOnWriteArrayList__private_t _private;
};

aeten_lang__CopyOnWriteArrayList * aeten_lang__CopyOnWriteArrayList__initialize(aeten_lang__CopyOnWriteArrayList *list, size_t element_size, size_t initial_capacity);

aeten_lang__List * aeten_lang__CopyOnWriteArrayList__new(size_t element_size, size_t initial_capacity);

void aeten_lang__CopyOnWriteArrayList__finalize(aeten_lang__List *list);

/** @see aeten_lang__List__get  */
void* aeten_lang__CopyOnWriteArrayList__get(aeten_lang__List *list, unsigned int position);

/** @see aeten_lang__List__set  */
void aeten_lang__CopyOnWriteArrayList__set(aeten_lang__List *list, unsigned int position, void *element);

/** @see aeten_lang__List__add  */
void aeten_lang__CopyOnWriteArrayList__add(aeten_lang__List *list, void *element);

/** @see aeten_lang__List__size  */
size_t aeten_lang__CopyOnWriteArrayList__size(aeten_lang__List *list);

#endif
