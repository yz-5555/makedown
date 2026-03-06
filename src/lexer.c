#include "lexer.h"
#include <string.h>

#define IS_STREAM(type) (type < TT_NEWLINE)
#define ERR_TOKENS_OUT_OF_BOUND -2

void lexer_init(Lexer *tok) {
    tok->line = 0;
    tok->pos = 0;
    tok->tkn_arr_len = 0;

    for (size_t i = 0; i < TOKENS_CAPACITY; i += 1) {
        tok->tkn_arr[i].count = 0;
        tok->tkn_arr[i].line = 0;
        tok->tkn_arr[i].pos = 0;
        strcpy(tok->tkn_arr[i].value, "");
    }
}
void lexer_print(const Lexer *lexer) {
    if (lexer->tkn_arr_len == 0)
        return;

    // clang-format off
    char *tt_map[14] = {
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
    for (size_t i = 0; i < lexer->tkn_arr_len; i += 1) {
        printf("%s | line: %d, pos: %d | count: %d | '%s'\n",
               tt_map[lexer->tkn_arr[i].type],
               lexer->tkn_arr[i].line,
               lexer->tkn_arr[i].pos,
               lexer->tkn_arr[i].count,
               lexer->tkn_arr[i].value);
    }
}
void tokenize(Lexer *lexer, const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("ERR: Failed to read the file.");
        return;
    }

    int letter = fgetc(file);
    while (letter != EOF && letter != ERR_TOKENS_OUT_OF_BOUND) {
        TokenType type = get_token_type(letter);
        if (IS_STREAM(type)) {
            letter = handle_tkn_stream(lexer, letter, type, file);
        } else if (type == TT_TEXT) {
            letter = handle_tkn_text(lexer, letter, file);
        } else {
            letter = handle_tkn_else(lexer, type, file);
        }
        lexer->pos += 1;
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
int handle_tkn_stream(Lexer *lexer, char letter, TokenType type, FILE *file) {
    if (lexer->tkn_arr_len + 1 > TOKENS_CAPACITY)
        return ERR_TOKENS_OUT_OF_BOUND;

    lexer->tkn_arr[lexer->tkn_arr_len].count = 1;
    lexer->tkn_arr[lexer->tkn_arr_len].pos = lexer->pos;

    int next_letter = 0;
    while ((next_letter = fgetc(file)) == letter) {
        lexer->tkn_arr[lexer->tkn_arr_len].count += 1;
        lexer->pos += 1;
    }

    lexer->tkn_arr[lexer->tkn_arr_len].line = lexer->line;
    lexer->tkn_arr[lexer->tkn_arr_len].type = type;

    lexer->tkn_arr_len += 1;

    return next_letter;
}
int handle_tkn_text(Lexer *lexer, char letter, FILE *file) {
    if (lexer->tkn_arr_len + 1 > TOKENS_CAPACITY)
        return ERR_TOKENS_OUT_OF_BOUND;

    lexer->tkn_arr[lexer->tkn_arr_len].count = 1;
    lexer->tkn_arr[lexer->tkn_arr_len].pos = lexer->pos;
    lexer->tkn_arr[lexer->tkn_arr_len].value[0] = letter;

    int next_letter = 0;
    int value_idx = 1;
    while (get_token_type(next_letter = fgetc(file)) == TT_TEXT) {
        lexer->tkn_arr[lexer->tkn_arr_len].count += 1;
        lexer->pos += 1;

        if (value_idx + 1 <= VALUE_CAPACITY) {
            lexer->tkn_arr[lexer->tkn_arr_len].value[value_idx] = next_letter;
            value_idx += 1;
        }
    }

    lexer->tkn_arr[lexer->tkn_arr_len].line = lexer->line;
    lexer->tkn_arr[lexer->tkn_arr_len].type = TT_TEXT;

    lexer->tkn_arr_len += 1;

    return next_letter;
}
int handle_tkn_else(Lexer *lexer, TokenType type, FILE *file) {
    if (lexer->tkn_arr_len + 1 > TOKENS_CAPACITY)
        return ERR_TOKENS_OUT_OF_BOUND;

    lexer->tkn_arr[lexer->tkn_arr_len].count = 1;
    lexer->tkn_arr[lexer->tkn_arr_len].line = lexer->line;
    lexer->tkn_arr[lexer->tkn_arr_len].pos = lexer->pos;
    lexer->tkn_arr[lexer->tkn_arr_len].type = type;

    lexer->tkn_arr_len += 1;

    if (type == TT_NEWLINE) {
        lexer->line += 1;
        lexer->pos = 0;
    }

    return fgetc(file);
}
