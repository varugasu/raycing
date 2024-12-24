namespace rl {
#include "raylib.h"
}

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  rl::InitWindow(screenWidth, screenHeight,
                 "raylib [core] example - basic window");

  rl::SetTargetFPS(60);

  while (!rl::WindowShouldClose()) {
    rl::BeginDrawing();

    rl::ClearBackground(rl::RAYWHITE);

    rl::DrawText("Congrats! You created your first window!", 190, 200, 20,
                 rl::LIGHTGRAY);

    rl::EndDrawing();
  }

  rl::CloseWindow();

  return 0;
}
