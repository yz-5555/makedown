#include "makedown.h"
#include <stdio.h>
#include <string.h>

void tok_init(Tokenizer *tokenizer) {
    tokenizer->line = 0;
    tokenizer->pos = 0;
    tokenizer->tokens_len = 0;
}
void tok_add_token(Tokenizer *tokenizer, uint32_t type, const char *value) {
    if (tokenizer->tokens_len + 1 > TOKENS_CAPACITY)
        return;

    tokenizer->tokens[tokenizer->tokens_len].line = tokenizer->line;
    tokenizer->tokens[tokenizer->tokens_len].pos = tokenizer->pos - strlen(value);
    tokenizer->tokens[tokenizer->tokens_len].type = type;
    strcpy(tokenizer->tokens[tokenizer->tokens_len].value, value);

    tokenizer->tokens_len += 1;
}
void tok_tokenize(Tokenizer *tokenizer, const char *path) {
    FILE *target = fopen(path, "r");
    if (target == NULL) {
        printf("ERR: Failed to read the file.");
        return;
    }

    int letter = 0;
    while ((letter = fgetc(target)) != EOF) {
        TokenType tt;
        switch (letter) {
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
            tok_add_token(tokenizer, tt, "");
            tokenizer->line += 1;
            tokenizer->pos = 0;
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
        tok_add_token(tokenizer, tt, "");
        tokenizer->pos += 1;
    }
}
