#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "raylib.hpp"

class GameObject {
 public:
  rl::Vector3 position;
  float rotation;
  rl::Vector3 scale;

  GameObject()
      : position{0.0f, 0.0f, 0.0f}, rotation(0), scale{1.0f, 1.0f, 1.0f} {}

  void Draw() {};
  void Update() {};
};

#endif
