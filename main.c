/*
	Binarnic Project

	(c) 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"

void print_help() {
	printf("binarnic - simple interpreter for expressions of binary mathematical logic\n");
	printf("\nSupported expressions:\n");
	printf("'1' - logical value of 'true'\n");
	printf("'0' - logical value of 'false'\n");
	printf("'!x' - logical NOT\n");
	printf("'x & y' - logical AND\n");
	printf("'x | y' - logical OR\n");
	printf("'x => y' - implication\n");
	printf("'x <=> y' - equality\n");
	printf("'a = <expression>' - set variable a\n");
	printf("'(', ')' - change operations priority with parenthesis\n");
}

void repl_loop() {
	char input[2048];

	printf("Type 'exit' to exit or 'help' to get short reference\n\n");

	parser_init();

	for(;;) {
		printf(">> ");
		if (fgets(input, sizeof(input), stdin)) {
			if (strcmp(input, "exit\n") == 0) break;
			if (strcmp(input, "help\n") == 0) {
				print_help();
				continue;
			}

			if (input[0] == '\n') continue;

			lexer_init(&input[0]);
			lexer_run();
			//lexer_dump();

			if (!lexer_has_error()) {
				parser_prepare();

				value_t result = parser_run();

				if (!parser_has_error()) {
					printf("%d\n", result);
				}
			}
		}
	}
}

int main(int argc, char const *argv[]) {
	printf("binarnic v.1.0.0 by MrOnlineCoder\n\n");

	repl_loop();

	return 0;
}