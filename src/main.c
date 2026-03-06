#include "lexer.h"

int main(int argc, char *argv[]) {
    Lexer t;
    lexer_init(&t);
    tokenize(&t, "./foo.md");
    lexer_print(&t);
    return 0;
}
