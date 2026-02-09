#ifndef MD_H
#define MD_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// clang-format off
typedef enum TokenType {
	TT_TEXT,
	TT_HASH,         // #
	TT_UNDERSCORE,   // _
	TT_STAR,         // *
	TT_NEWLINE,      // \n
	TT_DASH,         // -
	TT_LSQUARERACE,  // [
	TT_RSQUAREBRACE, // ]
	TT_LPAREN,       // (
	TT_RPAREN,       // )
	TT_BACKTICK,     // `
	TT_GREATERTHAN,  // >
	TT_BANG,         // !
} TokenType;
// clang-format on

typedef struct Token {
    uint32_t line, pos;
    TokenType type;
    char value[32];
} Token;

#define LINE_CAPACITY 128
#define TOKENS_CAPACITY 32
typedef struct Tokenizer {
    uint32_t line, pos;
    Token tokens[TOKENS_CAPACITY];
    size_t tokens_len;
} Tokenizer;
void tok_init(Tokenizer *tokenizer);
void tok_add_token(Tokenizer *tokenizer, uint32_t type, const char *value);
void tok_tokenize(Tokenizer *tokenizer, const char *path);

#endif // MD_H
