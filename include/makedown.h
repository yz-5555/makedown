#ifndef MAKEDOWN_H
#define MAKEDOWN_H

typedef enum { MT_H1 } MarkdownType;

typedef struct {
	MarkdownType md_type;
	char* content;
} MarkdownLine;

void render_markdown_line(const MarkdownLine* md_line);
void parse_markdown_line(const char* raw_string, MarkdownLine* md_line);

#endif
