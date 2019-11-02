/*
	Binarnic Project

	(c) 2019
*/

#include "parser.h"
#include "lexer.h"
#include "operations.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*

	ERRORS

*/
int parser_error = 0;

void raise_error() {
	parser_error = 1;
}


/*

	VARIABLES

*/

var_t vars[256];
size_t nvars = 0;;

value_t* get_variable(char* name);
void put_variable(char* name, value_t val);


/*
	
	GRAMMAR NODES

*/

value_t factor();
value_t conjunction();
value_t disjunction();
value_t implication();
value_t equality();
value_t expression();
value_t assign();
value_t statement();

value_t factor() {
	token_t tok = lexer_next();

	if (tok.type == TOKEN_CONST) {
		return tok.value;
	}

	if (tok.type == TOKEN_OP_NOT) {
		return OP_NOT(factor());
	}

	if (tok.type == TOKEN_LPAREN) {
		value_t a = expression();

		lexer_next();

		return a;
	}

	if (tok.type == TOKEN_ID) {
		value_t* t = get_variable(tok.str_value);

		if (!t) {
			raise_error();
			printf("parser error: unknown identifier '%s'\n", tok.str_value);
			return 0;
		}

		return *t;
	}

	raise_error();
	printf("parser error: unexpected token '%d'\n", tok.type);
	return 0;
}

value_t conjunction() {
	value_t a = factor();

	token_t tok = lexer_peek();

	if (tok.type == TOKEN_OP_AND) {
		lexer_next();
		return OP_AND(a, factor());
	} else {
		return a;
	}
}

value_t disjunction() {
	value_t a = conjunction();

	token_t tok = lexer_peek();

	if (tok.type == TOKEN_OP_OR) {
		lexer_next();
		return OP_OR(a, conjunction());
	} else {
		return a;
	}
}

value_t implication() {
	value_t a = disjunction();

	token_t tok = lexer_peek();

	if (tok.type == TOKEN_OP_IMP) {
		lexer_next();
		return OP_IMP(a, disjunction());
	} else {
		return a;
	}
}

value_t equality() {
	value_t a = implication();

	token_t tok = lexer_peek();

	if (tok.type == TOKEN_OP_EQ) {
		lexer_next();
		return OP_EQ(a, implication());
	} else {
		return a;
	}
}


value_t expression() {
	return equality();
}

value_t assign() {
	token_t left = lexer_next();

	token_t eq = lexer_next();

	value_t right = expression();

	put_variable(left.str_value, right);

	return right;
}

value_t statement() {
	if (lexer_peek().type == TOKEN_ID && lexer_peek_far(1).type == TOKEN_ASSIGN) {
		return assign();
	} else {
		return expression();
	}
}

value_t* get_variable(char* name) {
	for (size_t i = 0; i < nvars; i++) {
		if (strcmp(name, vars[i].name) == 0) {
			return &vars[i].value;
		}
	}

	return NULL;
}

void put_variable(char* name, value_t val) {
	for (size_t i = 0; i < nvars; i++) {
		if (strcmp(name, vars[i].name) == 0) {
			vars[i].value = val;
			return;
		}
	}

	strcpy(vars[nvars].name, name);
	vars[nvars].value = val;
	nvars++;
}

/*

	PUBLIC FUNCTIONS

*/

void parser_init() {
	parser_error = 0;
}

value_t parser_run() {
	value_t s = statement();

	if (parser_error) {
		return 0;
	}

	return s;
}

int parser_has_error() {
	return parser_error;
}