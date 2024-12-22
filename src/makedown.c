#include "makedown.h"
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

void render_markdown_line(const MarkdownLine* md_line)
{
	if (md_line->md_type == MT_H1) {
		DrawText(md_line->content, 100, 100, 60, BLACK);	
	}
}
void parse_markdown_line(const char* raw_string, MarkdownLine* md_line)
{
	md_line->md_type = MT_H1;

	size_t size = strlen(raw_string) + 1;
	md_line->content = (char*)malloc(size);
	strcpy(md_line->content, raw_string);
}
