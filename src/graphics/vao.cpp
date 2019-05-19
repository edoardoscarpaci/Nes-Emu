#include "../stdafx.h"

#include "../../vendor/glad/include/glad/glad.h"
#include "../../vendor/glfw3/GLFW/glfw3.h"
#include "vao.h"

namespace graphics {
VAO::VAO() { glad_glGenVertexArrays(1, &m_VAO); }
VAO::~VAO() { glad_glDeleteBuffers(1, &m_VAO); }

void VAO::bind() { glad_glBindVertexArray(m_VAO); }
void VAO::unbind() { glad_glBindVertexArray(0); }

void VAO::setVAO(unsigned int size, VBO dataObject) {
  bind();
  dataObject.bind();

  glad_glVertexAttribPointer(m_VBOs.size(), size, GL_FLOAT, GL_FALSE, 0, 0);
  glad_glEnableVertexAttribArray(m_VBOs.size());

  unbind();

  m_VBOs.emplace_back(dataObject);
}

void VAO::setVAO(unsigned int size, VBO dataObject, unsigned int stride,
                 unsigned int pointer) {
  bind();
  dataObject.bind();

  glad_glVertexAttribPointer(m_VBOs.size(), size, GL_FLOAT, GL_FALSE, stride,
                             (void *)pointer);
  glad_glEnableVertexAttribArray(m_VBOs.size());

  unbind();

  m_VBOs.emplace_back(dataObject);
}

} // namespace graphics
