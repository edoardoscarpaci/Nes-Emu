#pragma once
#include "../stdafx.h"

#include "ibo.h"
#include "vao.h"
#include "vbo.h"
#include "vec.h"

namespace graphics {
class Quad {
public:
  Quad(Vector2 topleft, Vector2 bottomRight);
  Quad();

  inline const Vector2 *getPosition() const { return m_Position.data(); };
  inline const Vector2 *getUV() const { return m_UV.data(); };
  inline const unsigned int &getVerticesCount() const {
    return m_Position.size();
  };
  inline VAO getVAO() const { return m_VAO; };
  inline IBO getIBO() const { return m_IBO; };

private:
  std::array<Vector2, 4> m_Position;
  std::array<Vector2, 4> m_UV;
  VAO m_VAO;
  IBO m_IBO;
};
} // namespace graphics
