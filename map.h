/*
	Binarnic Project

	(c) 2019
*/

#ifndef MAP_H
#define MAP_H 

#define MAX_ENTRIES 64

typedef struct {
  char key[64];
  int value;
} entry_t;

typedef struct {
  entry_t* entries;
  int count;
} map_t;

void map_init(map_t* m);

entry_t* map_get(map_t* m, char* key);

void map_put(map_t* m, char* key, int value);

void map_free(map_t* m);

#endif