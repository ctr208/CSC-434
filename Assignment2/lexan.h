// *******************************************************************
// File: lexan.h
// Author: Austin Baird
// Date: 04/29/2019
// Description: This is the header file for the lexan.  It includes
//              definitions for the token type, token, and symbol
//              table.
// *******************************************************************

#include <stdio.h>

#ifndef LEXAN

// This is meant to prevent this file from being included twice.
#define LEXAN

// Table sizes
#define SYMBOL_TABLE_CAPACITY 1000
#define MAX_TOKENS 10000



// *******************************************************************
// Data types
enum token_type { NONE = 101, OP, ID, INT, FLOAT };


struct symEntry {
	char name[BUFSIZ];
	enum token_type tokenType;
};


struct token {
	enum token_type tokenType;
	int intValue;               // If tokenType == INT
	float floatValue;           // If tokenType == FLOAT

	// MOD and DIV are operators of size 4 (including the '\0').
	// We could potentially have longer operators, but that is unlikely.
	char operator[10];          // If tokenType == OP

	// If the tokenType is an ID, the symbolEntry will hold the
	// index in the SymbolTable.
	int symbolEntry;            // If tokenType == ID

	int lineno;                 // Which source line is this token from.
								// This is useful for printing error
								// messages.
};
// *******************************************************************


// *******************************************************************
// Function declarations
int lexan();
void initSymbolTable();
int lookup(char* s);
int insert(char* s, enum token_type tokenType);
void printTable();
void emit(enum token_type tokenType, char* s, int tokenValInt,
	float tokenValFloat, int symbolTableId, int lineno);
void error(int c);
// *******************************************************************


// *******************************************************************
// Global Data
// These are declared as extern, which means that we are only declaring
// their existance, not instantiating them.  They are created in the lexan.c 
// file. The reason this is necessary is so that we can have declarations of
// this data to be used in other files, like parser.c, but we don't 
// want multiple instantiations.

extern int lineno;
extern int symTableSize;   // Last entry in the symbol table
extern int tokenTableSize;   // Last entry in the token table

// Symbol Table
extern struct symEntry SymbolTable[SYMBOL_TABLE_CAPACITY];

// Token Table
extern struct token ListOfTokens[MAX_TOKENS];

// *******************************************************************

#endif


