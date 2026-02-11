#include "makedown.h"

int main(int argc, char *argv[]) {
	Tokenizer t;
	tok_init(&t);
	tokenize(&t, "./foo.md");
	tok_print(&t);
    return 0;
}
