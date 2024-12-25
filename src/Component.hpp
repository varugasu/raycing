#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component {
 public:
  Component(GameObject* owner) : owner(owner) {}
  virtual ~Component() {}

  virtual void Update() {}
  virtual void Draw() {}

 protected:
  GameObject* owner;
};

#endif
