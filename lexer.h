/*
	Binarnic Project

	(c) 2019
*/

#ifndef LEXER_H
#define LEXER_H

#define TOKEN_CONST 0
#define TOKEN_OP_NOT 1
#define TOKEN_OP_AND 2
#define TOKEN_OP_OR 3
#define TOKEN_OP_IMP 4
#define TOKEN_OP_EQ 5
#define TOKEN_LPAREN 6
#define TOKEN_RPAREN 7

typedef struct {
	int type;
	int value;
} token_t;

void lexer_init(char* buf);
void lexer_run();
void lexer_dump();
int lexer_has_next();
token_t lexer_next();
token_t lexer_peek();
int lexer_has_error();

#endif