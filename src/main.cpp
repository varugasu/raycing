#include <vector>
#include "raylib.hpp"
#include "GameObject.hpp"
#include "Component.hpp"

class Model : public Component {
 public:
  rl::Model model;
  Model(GameObject* owner, const char* path) : Component(owner) {
    model = rl::LoadModel(path);
  }
  void Draw() { rl::DrawModel(model, owner->position, 1.0f, rl::WHITE); }
};

GameObject createModel(const char* path) {
  GameObject gameObject;
  gameObject.AddComponent<Model>(path);
  return gameObject;
}

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  rl::InitWindow(screenWidth, screenHeight,
                 "raylib [core] example - basic window");

  rl::Camera3D camera{0};
  camera.position = (rl::Vector3){10.0f, 10.0f, 10.0f};
  camera.target = (rl::Vector3){0.0f, 0.0f, 0.0f};
  camera.up = (rl::Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = rl::CAMERA_PERSPECTIVE;

  // Set up lighting
  rl::Vector3 lightPosition = {2.0f, 4.0f, 2.0f};
  rl::Color lightColor = rl::GRAY;

  // Load lighting shader
  rl::Shader shader =
      rl::LoadShader("shaders/lighting.vs", "shaders/lighting.fs");
  // Get shader locations
  int viewPosLoc = rl::GetShaderLocation(shader, "viewPos");
  int lightPosLoc = rl::GetShaderLocation(shader, "lightPos");
  shader.locs[rl::SHADER_LOC_VECTOR_VIEW] = viewPosLoc;
  int lightColorLoc = rl::GetShaderLocation(shader, "lightColor");
  shader.locs[rl::SHADER_LOC_COLOR_DIFFUSE] = lightColorLoc;

  GameObject car = createModel("models/car/car.obj");
  car.GetComponent<Model>()->model.materials[0].shader = shader;
  std::vector<GameObject> gameObjects;
  gameObjects.push_back(car);

  rl::SetTargetFPS(60);

  while (!rl::WindowShouldClose()) {
    rl::UpdateCamera(&camera, rl::CAMERA_PERSPECTIVE);

    rl::BeginDrawing();
    rl::ClearBackground(rl::RAYWHITE);

    rl::BeginMode3D(camera);

    float cameraPos[3] = {camera.position.x, camera.position.y,
                          camera.position.z};
    rl::SetShaderValue(shader, shader.locs[rl::SHADER_LOC_VECTOR_VIEW],
                       cameraPos, rl::SHADER_UNIFORM_VEC3);
    float lightPos[3] = {lightPosition.x, lightPosition.y, lightPosition.z};
    rl::SetShaderValue(shader, shader.locs[rl::SHADER_LOC_VECTOR_VIEW],
                       lightPos, rl::SHADER_UNIFORM_VEC3);
    float lightCol[3] = {(float)lightColor.r / 255.0f,
                         (float)lightColor.g / 255.0f,
                         (float)lightColor.b / 255.0f};

    rl::SetShaderValue(shader, viewPosLoc, cameraPos, rl::SHADER_UNIFORM_VEC3);
    rl::SetShaderValue(shader, lightPosLoc, lightPos, rl::SHADER_UNIFORM_VEC3);
    rl::SetShaderValue(shader, lightColorLoc, lightCol,
                       rl::SHADER_UNIFORM_VEC3);

    for (auto& gameObject : gameObjects) {
      gameObject.Draw();
      gameObject.Update();
    }

    rl::DrawCube((rl::Vector3){3.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f, rl::RED);
    rl::DrawGrid(10, 1.0f);

    rl::EndMode3D();

    rl::EndDrawing();
  }

  rl::CloseWindow();

  return 0;
}
