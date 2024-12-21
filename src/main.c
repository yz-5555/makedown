#include <raylib.h>

int main(void)
{
	InitWindow(800, 600, "Hello, Raylib!");

	while (!WindowShouldClose()) {
		BeginDrawing();
		{
			ClearBackground(WHITE);
			DrawText("Hello, Raylib!", 100, 100, 20, LIGHTGRAY);
		}
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
