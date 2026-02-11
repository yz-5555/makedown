#include "makedown.h"
#include <string.h>

#define IS_STREAM(type) (type < TT_NEWLINE)
#define ERR_TOKENS_OUT_OF_BOUND -2

void tok_init(Tokenizer *tok) {
    tok->line = 0;
    tok->pos = 0;
    tok->tokens_len = 0;

    for (size_t i = 0; i < TOKENS_CAPACITY; i += 1) {
        tok->tokens[i].count = 0;
        tok->tokens[i].line = 0;
        tok->tokens[i].pos = 0;
        strcpy(tok->tokens[i].value, "");
    }
}
void tok_print(const Tokenizer *tok) {
    if (tok->tokens_len == 0)
        return;

    // clang-format off
    char *token_type_map[14] = {
        // STREAM
        "TT_HASH",         // #
        "TT_UNDERSCORE",   // _
        "TT_STAR",         // *
        "TT_BACKTICK",     // `
        "TT_DASH",         // -
        // NOT STREAM
		"TT_NEWLINE",      // \n
        "TT_LSQUARERACE",  // [
        "TT_RSQUAREBRACE", // ]
        "TT_LPAREN",       // (
        "TT_RPAREN",       // )
        "TT_GREATERTHAN",  // >
		"TT_TEXT",
        "TT_BANG",         // !
    };
    // clang-format on
    for (size_t i = 0; i < tok->tokens_len; i += 1) {
        printf("%s | line: %d, pos: %d | count: %d | '%s'\n",
               token_type_map[tok->tokens[i].type],
               tok->tokens[i].line,
               tok->tokens[i].pos,
               tok->tokens[i].count,
               tok->tokens[i].value);
    }
}
void tokenize(Tokenizer *tok, const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("ERR: Failed to read the file.");
        return;
    }

    int letter = fgetc(file);
    while (letter != EOF && letter != ERR_TOKENS_OUT_OF_BOUND) {
        TokenType type = get_token_type(letter);
        if (IS_STREAM(type)) {
            letter = append_token_stream(tok, letter, type, file);
        } else if (type == TT_TEXT) {
            letter = append_token_text(tok, letter, file);
        } else {
            letter = append_token(tok, type, file);
        }
        tok->pos += 1;
    }

    fclose(file);
}
TokenType get_token_type(char letter) {
    switch (letter) {
    case '#':
        return TT_HASH;
    case '_':
        return TT_UNDERSCORE;
    case '*':
        return TT_STAR;
    case '`':
        return TT_BACKTICK;
    case '-':
        return TT_DASH;
    case '\n':
        return TT_NEWLINE;
    case '[':
        return TT_LSQUARERACE;
    case ']':
        return TT_RSQUAREBRACE;
    case '(':
        return TT_LPAREN;
    case ')':
        return TT_RPAREN;
    case '>':
        return TT_GREATERTHAN;
    case '!':
        return TT_BANG;
    default:
        return TT_TEXT;
    }
}
int append_token_stream(Tokenizer *tok, char letter, TokenType type, FILE *file) {
    if (tok->tokens_len + 1 > TOKENS_CAPACITY)
        return ERR_TOKENS_OUT_OF_BOUND;

    tok->tokens[tok->tokens_len].count = 1;
    tok->tokens[tok->tokens_len].pos = tok->pos;

    int next_letter = 0;
    while ((next_letter = fgetc(file)) == letter) {
        tok->tokens[tok->tokens_len].count += 1;
        tok->pos += 1;
    }

    tok->tokens[tok->tokens_len].line = tok->line;
    tok->tokens[tok->tokens_len].type = type;

    tok->tokens_len += 1;

    return next_letter;
}
int append_token_text(Tokenizer *tok, char letter, FILE *file) {
    if (tok->tokens_len + 1 > TOKENS_CAPACITY)
        return ERR_TOKENS_OUT_OF_BOUND;

    tok->tokens[tok->tokens_len].count = 1;
    tok->tokens[tok->tokens_len].pos = tok->pos;
    tok->tokens[tok->tokens_len].value[0] = letter;

    int next_letter = 0;
    int value_idx = 1;
    while (get_token_type(next_letter = fgetc(file)) == TT_TEXT) {
        tok->tokens[tok->tokens_len].count += 1;
        tok->pos += 1;

        if (value_idx + 1 <= VALUE_CAPACITY) {
            tok->tokens[tok->tokens_len].value[value_idx] = next_letter;
            value_idx += 1;
        }
    }

    tok->tokens[tok->tokens_len].line = tok->line;
    tok->tokens[tok->tokens_len].type = TT_TEXT;

    tok->tokens_len += 1;

    return next_letter;
}
int append_token(Tokenizer *tok, TokenType type, FILE *file) {
    if (tok->tokens_len + 1 > TOKENS_CAPACITY)
        return ERR_TOKENS_OUT_OF_BOUND;

    tok->tokens[tok->tokens_len].count = 1;
    tok->tokens[tok->tokens_len].line = tok->line;
    tok->tokens[tok->tokens_len].pos = tok->pos;
    tok->tokens[tok->tokens_len].type = type;

    tok->tokens_len += 1;

    if (type == TT_NEWLINE) {
        tok->line += 1;
        tok->pos = 0;
    }

    return fgetc(file);
}
