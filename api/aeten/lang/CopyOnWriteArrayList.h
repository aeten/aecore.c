#ifndef AETEN_LANG_COPYONWRITEARRAYLIST_H
#define AETEN_LANG_COPYONWRITEARRAYLIST_H

#include "aeten/lang/import.h"
#include "aeten/lang/List.h"

implementation(aeten_lang__CopyOnWriteArrayList, aeten_lang__List) {
	_aeten_lang__object__impl
	size_t capacity;
	size_t size;
	size_t element_size;
	void *elements;
};

aeten_lang__CopyOnWriteArrayList * aeten_lang__CopyOnWriteArrayList__init(aeten_lang__CopyOnWriteArrayList *list, size_t element_size, size_t initial_capacity);

aeten_lang__CopyOnWriteArrayList * aeten_lang__CopyOnWriteArrayList__new(size_t element_size, size_t initial_capacity);
void aeten_lang__CopyOnWriteArrayList__finalize(aeten_lang__CopyOnWriteArrayList *list);

/** @see aeten_lang__List__get  */
void* aeten_lang__CopyOnWriteArrayList__get(aeten_lang__CopyOnWriteArrayList *list, unsigned int position);

/** @see aeten_lang__List__set  */
void aeten_lang__CopyOnWriteArrayList__set(aeten_lang__CopyOnWriteArrayList *list, unsigned int position, void *element);

/** @see aeten_lang__List__add  */
void aeten_lang__CopyOnWriteArrayList__add(aeten_lang__CopyOnWriteArrayList *list, void *element);

/** @see aeten_lang__List__size  */
size_t aeten_lang__CopyOnWriteArrayList__size(aeten_lang__CopyOnWriteArrayList *list);

#endif
