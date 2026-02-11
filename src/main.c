#include "makedown.h"

int main(int argc, char *argv[]) {
    TokenArray t;
    tok_init(&t);
    tok_tokenize(&t, "./foo.md");
	tok_print(&t);
    return 0;
}
