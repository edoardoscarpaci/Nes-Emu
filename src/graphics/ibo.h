#pragma once
#include "../stdafx.h"

namespace graphics {

class IBO {
public:
  IBO(unsigned int size, unsigned int *data);
  IBO();
  void bind();
  void unbind();

  inline const unsigned int getSize() const { return m_Data.size(); };
  inline const unsigned int *getData() const { return m_Data.data(); };
  inline const unsigned int getDataIndex(unsigned int index) const {
    if (index < m_Data.size())
      return m_Data[index];
    return -1;
  };
  inline const unsigned int getIBO() const { return m_IBO; };

private:
  std::vector<unsigned int> m_Data;
  unsigned int m_IBO;
};

} // namespace graphics
