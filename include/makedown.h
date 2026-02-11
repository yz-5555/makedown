#ifndef MD_H
#define MD_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

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

#define VALUE_CAPACITY 64
typedef struct Token {
    uint32_t count;
    uint32_t line, pos;
    TokenType type;
    char value[VALUE_CAPACITY];
} Token;

#define TOKENS_CAPACITY 64
typedef struct Tokenizer {
    uint32_t line, pos;
    Token tokens[TOKENS_CAPACITY];
    size_t tokens_len;
} Tokenizer;
void tok_init(Tokenizer *tok);
void tok_print(const Tokenizer *tok);

void tokenize(Tokenizer *tok, const char *path);
TokenType get_token_type(char letter);
int append_token_stream(Tokenizer *tok, char letter, TokenType type, FILE *file);
int append_token_text(Tokenizer *tok, char letter, FILE *file);
int append_token(Tokenizer *tok, TokenType type, FILE *file);

#endif // MD_H
