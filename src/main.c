#include "makedown.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    Tokenizer t;
    tok_init(&t);
    tok_tokenize(&t, "./foo.md");
    for (int i = 0; i < t.tokens_len; i += 1) {
        printf("[%d] (%d, %d), '%s'\n", t.tokens[i].type, t.tokens[i].pos, t.tokens[i].line, t.tokens[i].value);
    }
    return 0;
}

// TODO
// 1. enum tostring for testing
// 2. append letter to one string var if it's TT_TEXT
// 3. remove useless space
