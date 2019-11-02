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
	
	GRAMMAR NODES

*/

value_t factor();
value_t conjunction();
value_t disjunction();
value_t implication();
value_t equality();
value_t expression();

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



/*

	PUBLIC FUNCTIONS

*/

void parser_init() {

}

value_t parser_run() {
	return expression();
}