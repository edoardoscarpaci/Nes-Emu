#include "vbo.h"
#include "../../vendor/glad/include/glad/glad.h"
#include "../../vendor/glfw3/GLFW/glfw3.h"
#include "../stdafx.h"

namespace graphics {

VBO::VBO(unsigned int size) : m_Size(size) {
  glad_glGenBuffers(1, &m_VBO);
  bind();
  glad_glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
  unbind();
}

VBO::VBO(unsigned int size, void *data) : m_Size(size) {
  glad_glGenBuffers(1, &m_VBO);
  bind();
  glad_glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  unbind();
}

VBO::~VBO() { glad_glDeleteBuffers(1, &m_VBO); }

void VBO::setData(void *data) {
  bind();
  glad_glBufferSubData(GL_ARRAY_BUFFER, 0, m_Size, data);
  unbind();
}

void VBO::setRangeData(unsigned int offset, unsigned int size, void *data) {
  bind();
  glad_glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
  unbind();
}

void VBO::unbind() { glad_glBindBuffer(GL_ARRAY_BUFFER, m_VBO); }
void VBO::bind() { glad_glBindBuffer(GL_ARRAY_BUFFER, m_VBO); }
} // namespace graphics
