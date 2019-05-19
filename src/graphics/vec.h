#pragma once
#include "../stdafx.h"
namespace graphics {
struct Vector2 {
  float x;
  float y;

  Vector2(float x, float y) {
    this->x = x;
    this->y = y;
  };

  Vector2() {
    this->x = 0;
    this->y = 0;
  };

  Vector2 &operator=(const Vector2 &v) {
    this->x = v.x;
    this->y = v.y;
    return *this;
  }
};
} // namespace graphics
