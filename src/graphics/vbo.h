#pragma once
#include "../stdafx.h"

namespace graphics {
class VBO {
public:
  VBO(unsigned int size);
  VBO(unsigned int size, void *data);
  ~VBO();
  void setData(void *data);
  void setRangeData(unsigned int offset, unsigned int size, void *data);
  void bind();
  void unbind();

  inline const unsigned int getSize() const { return m_Size; };
  inline const unsigned int getVBO() const { return m_VBO; };

private:
  unsigned int m_Size;
  unsigned int m_VBO;
};

} // namespace graphics
