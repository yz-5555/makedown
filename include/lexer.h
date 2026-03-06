#ifndef LEXER_H 
#define LEXER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "utils.h"

// clang-format off
typedef enum TokenType {
	// STREAM
	TT_HASH,         // #
	TT_UNDERSCORE,   // _
	TT_STAR,         // *
	TT_BACKTICK,     // `
	TT_DASH,         // -
	// NOT STREAM
	TT_NEWLINE,      // \n
	TT_LSQUARERACE,  // [
	TT_RSQUAREBRACE, // ]
	TT_LPAREN,       // (
	TT_RPAREN,       // )
	TT_GREATERTHAN,  // >
	TT_BANG,         // !
	TT_TEXT,
} TokenType;
// clang-format on

typedef struct Token {
    uint32_t count;
    uint32_t line, pos;
    TokenType type;
    char value[VALUE_CAPACITY];
} Token;

#define TOKENS_CAPACITY 64
typedef struct Lexer {
    uint32_t line, pos;
    Token tkn_arr[TOKENS_CAPACITY];
    size_t tkn_arr_len;
} Lexer;
void lexer_init(Lexer *tok);
void lexer_print(const Lexer *tok);

void tokenize(Lexer *lexer, const char *path);
TokenType get_token_type(char letter);
int handle_tkn_stream(Lexer *lexer, char letter, TokenType type, FILE *file);
int handle_tkn_text(Lexer *lexer, char letter, FILE *file);
int handle_tkn_else(Lexer *lexer, TokenType type, FILE *file);

#endif // LEXER_H
