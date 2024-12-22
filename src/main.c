#include <raylib.h>
#include "makedown.h"

int main(int argc, char* argv[])
{
	InitWindow(800, 600, "Hello, Raylib!");
	
	MarkdownLine md_line;
	parse_markdown_line("Hello, H1!", &md_line);

	while (!WindowShouldClose()) {
		BeginDrawing();
		{
			ClearBackground(WHITE);
			render_markdown_line(&md_line);
		}
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
