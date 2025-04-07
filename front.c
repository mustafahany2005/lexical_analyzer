#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
int inputIndex;
char input[100];

void addChar();
void getChar();
void getNonBlank();
int lex();
void printTokenType(int tokenCode);

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

#define IDENT 1      // Identifier
#define INT_LIT 2    // Number
#define ASSIGN_OP 3  // Operator
#define ADD_OP 3     // Operator
#define SUB_OP 3     // Operator
#define MULT_OP 3    // Operator
#define DIV_OP 3     // Operator
#define LEFT_PAREN 4 // Left Parenthesis
#define RIGHT_PAREN 5 // Right Parenthesis

int main() {
    // Default input
    sprintf(input, "Mustafa = ( 2005 + 20 ) * 10");
    inputIndex = 0;
    printf("Default input: %s\n", input);
    getChar();
    do {
        lex();
    } while (nextToken != EOF);

    // Single user input
    printf("\nEnter an expression: ");
    fgets(input, 100, stdin);
    inputIndex = 0;
    printf("Processing input: %s", input);
    getChar();
    do {
        lex();
    } while (nextToken != EOF);

    printf("Exiting program.\n");
    exit(0);
}

int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    case '=':
        addChar();
        nextToken = ASSIGN_OP;
        break;
    default:
        addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}

void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else
        printf("Error - lexeme is too long \n");
}

void getChar() {
    if (input[inputIndex] != '\0') {
        nextChar = input[inputIndex++];
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else
        charClass = EOF;
}

void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

int lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;
    case EOF:
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = 0;
        break;
    }
    printTokenType(nextToken);
    return nextToken;
}

void printTokenType(int tokenCode) {
    if (tokenCode == EOF) {
        printf("Token Type: End of Input, Token Code: -1, Lexeme: %s\n", lexeme);
    }
    else if (tokenCode == IDENT) {
        printf("Token Type: Identifier, Token Code: 1, Lexeme: %s\n", lexeme);
    }
    else if (tokenCode == INT_LIT) {
        printf("Token Type: Number, Token Code: 2, Lexeme: %s\n", lexeme);
    }
    else if (tokenCode == ASSIGN_OP || tokenCode == ADD_OP || tokenCode == SUB_OP ||
        tokenCode == MULT_OP || tokenCode == DIV_OP) {
        printf("Token Type: Operator, Token Code: 3, Lexeme: %s\n", lexeme);
    }
    else if (tokenCode == LEFT_PAREN) {
        printf("Token Type: Left Parenthesis, Token Code: 4, Lexeme: %s\n", lexeme);
    }
    else if (tokenCode == RIGHT_PAREN) {
        printf("Token Type: Right Parenthesis, Token Code: 5, Lexeme: %s\n", lexeme);
    }
}