/*****************************************************************
File: lexan.c
Author: Austin Baird
Date Written: 04/29/1997

Description: This program will read from stdin, tokenize it, build
			a symbol table, and produce an array of tokens.

			The lexicon consists of:
				1) Operators: + - * / MOD DIV ()
				2) Names / Symbols:
					a) Must bein is alpha or underscore ('_')
					b) May contain any number of alphanumeric or underscores
				3) Integers: [0-9][0-9]*
				4) Floating-points: [0-9][0-9]*.[0-9]*
*****************************************************************/


#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include"lexan.h"


/*
Global Data

This is where they are actually created.
*/

int lineno = 1;
int symTableSize = 0;
int tokenTableSize = 0;

//Symbol Table
struct symEntry SymbolTable[SYMBOL_TABLE_CAPACITY];

//Token Table
struct token ListOfTokens[MAX_TOKENS];

//***********************************************************


//**************************************
//Function: lexan()
// Parameters: none
// Return 0 on success, 1 on error
// Description: Process the input until an EOF and tokenize it. This will
//		build a table of tokens as well as the symbol table.
//**************************************
int lexan() {
	static int state = 0;

	char buffer[BUFSIZ];
	int c, i = 0, id;

	enum token_type tokenType;
	int tokenValInt = 0;
	float tokenValFLoat = 0.0;
	float decimalPlace = 0.1;

	while (1) {

		c = getchar();

		switch (state) {

		case 0:
			tokenValInt = 0;
			tokenValFLoat = 0.0;
			decimalPlace = 0.1;

			if (c == ' ' || c == '\t' || c == '\n') {
				state = 0;
				if (c == "\n") {
					lineno++;
				}
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
				tokenType = OP;
				buffer[0] = c;
				buffer[1] = '\0';
				state = 1;
			}
			else if (isalpha(c) || c == '_') {
				buffer[i++] = c;
				state = 2;
			}
			else if (isdigit(c)) {
				tokenValInt = c - '0';
				state = 3;
			}
			else if (c == EOF) {
				ungetc(c, stdin);
				state = 5;
			}
			else {
				error(c);
				return 1;
			}
			break;
		}
	}
}

void initSymbolTable() {

}
int lookup(char* s) {
	return 1;
}
int insert(char* s, enum token_type tokenType) {
	return 1;
}
void printTable() {
	for (int i = 0; i < MAX_TOKENS; i++) {
		switch (ListOfTokens[i].tokenType) {

			case(OP):

				printf("Token: OP - %s", ListOfTokens[i].operator);
				break;

			case(ID):
				printf("Token: ID - %i", ListOfTokens[i].symbolEntry);
				break;

			case(FLOAT):
				printf("Token: FLOAT - %f", ListOfTokens[i].floatValue);
				break;

			case(INT):
				printf("Token: INT - %i", ListOfTokens[i].intValue);
				break;

			case(NONE):
				printf("Token: NONE");
				break;
		}
	}
}
void emit(enum token_type tokenType, char* s, int tokenValInt, float tokenValFloat, int symbolTableId, int lineno) {

}
void error(int c) {
	fprintf(stderr, "Error with (%i) at line %i \n", c, lineno);
}