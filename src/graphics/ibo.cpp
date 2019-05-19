#include "../stdafx.h"

#include "../../vendor/glad/include/glad/glad.h"
#include "../../vendor/glfw3/GLFW/glfw3.h"
#include "ibo.h"

namespace graphics {
IBO::IBO(unsigned int size, unsigned int *data) {
  glad_glGenBuffers(1, &m_IBO);
  bind();
  glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  unbind();
}

void IBO::bind() { glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO); }
void IBO::unbind() { glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

} // namespace graphics
