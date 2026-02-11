#ifndef MD_H
#define MD_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// clang-format off
typedef enum TokenType {
	TT_TEXT,
	TT_SPACE,
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

#define TOKEN_ARRAY_CAPACITY 32
typedef struct TokenArray {
    Token data[TOKEN_ARRAY_CAPACITY];
    size_t len;
} TokenArray;
void tok_init(TokenArray *tok);
void tok_add_token(TokenArray *tok, uint32_t line, uint32_t pos, TokenType type, const char *value);
void tok_tokenize(TokenArray *tok, const char *path);
void tok_print(const TokenArray *tok);

#endif // MD_H
