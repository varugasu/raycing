#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <vector>
#include "raylib.hpp"
#include "Component.hpp"

class GameObject {
 public:
  rl::Vector3 position;
  float rotation;
  rl::Vector3 scale;

  std::vector<std::shared_ptr<Component>> components;

  GameObject()
      : position{0.0f, 0.0f, 0.0f}, rotation{0.0f}, scale{1.0f, 1.0f, 1.0f} {}

  template <typename T, typename... Args>
  std::shared_ptr<T> AddComponent(Args&&... args) {
    auto comp = std::make_shared<T>(this, std::forward<Args>(args)...);
    components.push_back(comp);
    return comp;
  }

  // Retrieve a component by type (optional convenience method)
  template <typename T>
  std::shared_ptr<T> GetComponent() {
    for (auto& comp : components) {
      auto casted = std::dynamic_pointer_cast<T>(comp);
      if (casted) return casted;
    }
    return nullptr;
  }

  void Draw() {
    for (auto& component : components) {
      component->Draw();
    }
  };
  void Update() {
    for (auto& component : components) {
      component->Update();
    }
  };
};

#endif
