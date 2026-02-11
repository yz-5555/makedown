#include "makedown.h"
#include <stdio.h>
#include <string.h>

void tok_init(TokenArray *tok) {
    tok->len = 0;
}
void tok_add_token(TokenArray *tok, uint32_t line, uint32_t pos, uint32_t type, const char *value) {
    if (tok->len + 1 > TOKEN_ARRAY_CAPACITY)
        return;

    tok->data[tok->len].line = line;
    tok->data[tok->len].pos = pos - strlen(value);
    tok->data[tok->len].type = type;
    strcpy(tok->data[tok->len].value, value);

    tok->len += 1;
}
void tok_tokenize(TokenArray *tok, const char *path) {
    FILE *target = fopen(path, "r");
    if (target == NULL) {
        printf("ERR: Failed to read the file.");
        return;
    }

    int letter = 0;
    uint32_t line = 0, pos = 0;

    while ((letter = fgetc(target)) != EOF) {
        TokenType tt;
        switch (letter) {
		case ' ':
			tt = TT_SPACE;
			break;
        case '#':
            tt = TT_HASH;
            break;
        case '_':
            tt = TT_UNDERSCORE;
            break;
        case '*':
            tt = TT_STAR;
            break;
        case '\n':
            tt = TT_NEWLINE;
            tok_add_token(tok, line, pos, tt, "");
            line += 1;
            pos = 0;
            continue;
        case '-':
            tt = TT_DASH;
            break;
        case '[':
            tt = TT_LSQUARERACE;
            break;
        case ']':
            tt = TT_RSQUAREBRACE;
            break;
        case '(':
            tt = TT_LPAREN;
            break;
        case ')':
            tt = TT_RPAREN;
            break;
        case '`':
            tt = TT_BACKTICK;
            break;
        case '>':
            tt = TT_GREATERTHAN;
            break;
        case '!':
            tt = TT_BANG;
            break;
        default:
            tt = TT_TEXT;
            break;
        }
        tok_add_token(tok, line, pos, tt, "");
        pos += 1;
    }
}
void tok_print(const TokenArray *tok) {
    char *token_type_map[14] = {
        "TT_TEXT",
		"TT_SPACE",
        "TT_HASH",         // #
        "TT_UNDERSCORE",   // _
        "TT_STAR",         // *
        "TT_NEWLINE",      // \n
        "TT_DASH",         // -
        "TT_LSQUARERACE",  // [
        "TT_RSQUAREBRACE", // ]
        "TT_LPAREN",       // (
        "TT_RPAREN",       // )
        "TT_BACKTICK",     // `
        "TT_GREATERTHAN",  // >
        "TT_BANG",         // !
    };
    for (size_t i = 0; i < tok->len; i += 1) {
        printf("%s | line: %d, pos: %d | '%s'\n",
               token_type_map[tok->data[i].type],
               tok->data[i].line,
               tok->data[i].pos,
               tok->data[i].value);
    }
}
