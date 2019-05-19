#pragma once
#include "../stdafx.h"
namespace graphics {

class Texture {
public:
  Texture();
  Texture(unsigned int w, unsigned int h);
  ~Texture();

  void bind();
  void unbind();

  void setPixel(unsigned int x, unsigned int y, unsigned int color);
  void clear();

  void flush();
  inline unsigned int getWidth() const { return m_Width; };
  inline unsigned int getHeight() const { return m_Height; };
  inline unsigned int getTexture() const { return m_TextureID; };

private:
  unsigned int m_Width;
  unsigned int m_Height;
  unsigned int m_TextureID;
  unsigned int *m_Buffer;
};

} // namespace graphics
