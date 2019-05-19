#include "quad.h"
#include "../stdafx.h"
namespace graphics {

Quad::Quad(Vector2 topRigth, Vector2 bottomRight) {

  m_Position[0] = topRigth;
  m_Position[1] = Vector2(topRigth.x, bottomRight.y);
  m_Position[2] = Vector2(bottomRight.x, topRigth.y);
  m_Position[3] = bottomRight;

  m_UV[0] = Vector2(0, 1);
  m_UV[1] = Vector2(0, 0);
  m_UV[2] = Vector2(1, 0);
  m_UV[2] = Vector2(1, 1);

  VBO positionVbo = VBO(4, m_Position.data());
  VBO UvVbo = VBO(4, m_UV.data());

  unsigned int indexes[6]{1, 2, 3, 2, 4, 3};

  m_IBO = IBO(6, indexes);
  m_VAO.setVAO(2, positionVbo);
  m_VAO.setVAO(2, UvVbo);
}

Quad::Quad() {
  m_Position[0] = Vector2(-1, 1);
  m_Position[1] = Vector2(-1, -1);
  m_Position[2] = Vector2(1, 1);
  m_Position[3] = Vector2(1, -1);

  m_UV[0] = Vector2(0, 1);
  m_UV[1] = Vector2(0, 0);
  m_UV[2] = Vector2(1, 0);
  m_UV[2] = Vector2(1, 1);

  VBO positionVbo = VBO(4, m_Position.data());
  VBO UvVbo = VBO(4, m_UV.data());

  unsigned int indexes[6]{1, 2, 3, 2, 4, 3};

  m_IBO = IBO(6, indexes);
  m_VAO.setVAO(2, positionVbo);
  m_VAO.setVAO(2, UvVbo);
}
} // namespace graphics
