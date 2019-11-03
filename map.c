/*
	Binarnic Project

	(c) 2019
*/

#include "map.h"

#include <stdlib.h>
#include <string.h>

void map_init(map_t* m) {
  m->entries = malloc(sizeof(entry_t) * MAX_ENTRIES);
  m->count = 0;
}

entry_t* map_get(map_t* m, char* key) {
	for (int i = 0; i < m->count; i++) {
		entry_t* e = &m->entries[i];
		if (strcmp(key, e->key) == 0) {
			return e;
		}
	}

	return NULL;
}

void map_put(map_t* m, char* key, int value) {
	entry_t* e = map_get(m, key);

	if (e) {
		e->value = value;
		return;
	}

	int idx = m->count;

	strcpy(m->entries[idx].key, key);
	m->entries[idx].value = value;
	m->count++;
}

void map_free(map_t* m) {
	free(m->entries);
	m->count = 0;
}