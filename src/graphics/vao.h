#pragma once

#include "../stdafx.h"
#include "vbo.h"
namespace graphics {

class VAO {
public:
  VAO();
  ~VAO();
  void bind();
  void unbind();

  void setVAO(unsigned int size, VBO dataObject);
  void setVAO(unsigned int size, VBO dataObject, unsigned int stride,
              unsigned int pointer);

  inline const unsigned int getVAO() const { return m_VAO; };
  inline VBO getVBO(unsigned int index) const {
    if (index < m_VBOs.size())
      return m_VBOs[index];
    return NULL;
  }

private:
  std::vector<VBO> m_VBOs;
  unsigned int m_VAO;
};

} // namespace graphics
