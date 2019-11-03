/*
	Binarnic Project

	(c) 2019
*/

#ifndef PARSER_H
#define PARSER_H

typedef int value_t;

typedef struct {
	char name[64];
	int value;
} var_t;

void parser_init();
void parser_prepare();
value_t parser_run();
int parser_has_error();
void parser_cleanup();

#endif