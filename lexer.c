/*
	Binarnic Project

	(c) 2019
*/

#include "lexer.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* current_buffer = NULL;

token_t tokens[512];
size_t ntokens;
size_t tok_iter;

int lexer_error = 0;

static void lexer_push(token_t t) {
	tokens[ntokens] = t;
	ntokens++;
}

void lexer_init(char* buf) {
	current_buffer = buf;

	ntokens = 0;
	tok_iter = 0;
	lexer_error = 0;
}

void lexer_run() {
	char* cp = current_buffer;

	while (*cp != '\n') {
		char c = *cp;
		cp++;

		token_t tok;

		if (c == ' ' || c == '\t') {
			continue;
		}

		if (c == '0') {
			tok.type = TOKEN_CONST;
			tok.value = 0;
			lexer_push(tok);
			continue;
		}

		if (c == '1') {
			tok.type = TOKEN_CONST;
			tok.value = 1;
			lexer_push(tok);
			continue;
		}

		if (c == '!') {
			tok.type = TOKEN_OP_NOT;
			tok.value = 0;
			lexer_push(tok);
			continue;
		}

		if (c == '&') {
			tok.type = TOKEN_OP_AND;
			tok.value = 0;
			lexer_push(tok);
			continue;
		}

		if (c == '|') {
			tok.type = TOKEN_OP_OR;
			tok.value = 0;
			lexer_push(tok);
			continue;
		}

		if (c == '(') {
			tok.type = TOKEN_LPAREN;
			tok.value = 0;
			lexer_push(tok);
			continue;
		}

		if (c == ')') {
			tok.type = TOKEN_RPAREN;
			tok.value = 0;
			lexer_push(tok);
			continue;
		}		

		if (c == '=') {
			c = *cp++;

			tok.value = 0;

			if (c == '>') {
				tok.type = TOKEN_OP_IMP;
			} 

			lexer_push(tok);
			continue;
		}

		if (c == '<') {
			c = *cp++;
			char c2 = *cp++;

			if (c == '=' && c2 == '>') {
				tok.value = 0;
				tok.type = TOKEN_OP_EQ;
			}

			lexer_push(tok);
			continue;
		}

		printf("lexer error: unknown token '%c'\n", c);
		lexer_error = 1;
		break;
	}
}

void lexer_dump() {
	for (size_t i = 0; i < ntokens; i++) {
		token_t tok = tokens[i];

		printf("#%zu => type: %d, value: %d\n", i, tok.type, tok.value);
	}
}

int lexer_has_next() {
	return tok_iter < ntokens;
}

token_t lexer_next() {
	return tokens[tok_iter++];
}

token_t lexer_peek() {
	return tokens[tok_iter];
}

int lexer_has_error() {
	return lexer_error;
}