/*
	Binarnic Project

	(c) 2019
*/

#include "lexer.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

char* current_buffer = NULL;

token_t tokens[512];
size_t ntokens;
size_t tok_iter;

int lexer_error = 0;

token_t EOF_TOKEN;

static void lexer_push(token_t t) {
	tokens[ntokens] = t;
	ntokens++;
}

void lexer_init(char* buf) {
	current_buffer = buf;

	ntokens = 0;
	tok_iter = 0;
	lexer_error = 0;

	EOF_TOKEN.type = TOKEN_EOF;
	EOF_TOKEN.value = 0;
	EOF_TOKEN.str_value[0] = '\0';
}

void lexer_run() {
	char* cp = current_buffer;

	while (*cp != '\n') {
		char c = *cp;
		cp++;

		token_t tok;
		tok.value = 0;
		tok.str_value[0] = '\0';

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
			lexer_push(tok);
			continue;
		}

		if (c == '&') {
			tok.type = TOKEN_OP_AND;
			lexer_push(tok);
			continue;
		}

		if (c == '|') {
			tok.type = TOKEN_OP_OR;
			lexer_push(tok);
			continue;
		}

		if (c == '(') {
			tok.type = TOKEN_LPAREN;
			lexer_push(tok);
			continue;
		}

		if (c == ')') {
			tok.type = TOKEN_RPAREN;
			lexer_push(tok);
			continue;
		}		

		if (c == '=') {
			c = *cp++;

			if (c == '>') {
				tok.type = TOKEN_OP_IMP;
			} else {
				tok.type = TOKEN_ASSIGN;
				cp--;
			} 

			lexer_push(tok);
			continue;
		}

		if (c == '<') {
			c = *cp++;
			char c2 = *cp++;

			if (c == '=' && c2 == '>') {
				tok.type = TOKEN_OP_EQ;
			}

			lexer_push(tok);
			continue;
		}

		if (isalpha(c)) {
			int idx = 1;
			tok.str_value[0] = c;
			while (*cp && isalpha(*cp)) {
				tok.str_value[idx] = *cp;
				cp++;
				idx++;
			}

			tok.str_value[idx] = '\0';

			tok.type = TOKEN_ID;
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

		printf("#%zu => type: %d, value: %d, str_value = %s\n", i, tok.type, tok.value, tok.str_value);
	}
}

int lexer_has_next() {
	return tok_iter < ntokens;
}

token_t lexer_next() {
	if (!lexer_has_next()) {
		return EOF_TOKEN;
	}
	return tokens[tok_iter++];
}

token_t lexer_peek() {
	if (tok_iter >= ntokens) return EOF_TOKEN;
	return tokens[tok_iter];
}

token_t lexer_peek_far(int d) {
	if (tok_iter+d >= ntokens) return EOF_TOKEN;
	return tokens[tok_iter+d];
}

int lexer_has_error() {
	return lexer_error;
}