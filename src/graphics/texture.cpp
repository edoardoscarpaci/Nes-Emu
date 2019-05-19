#include "texture.h"
#include "../../vendor/glad/include/glad/glad.h"
namespace graphics {

Texture::Texture() : m_Width(256), m_Height(256) {
  m_Buffer = new unsigned int[m_Width * m_Height];

  clear();
  glad_glGenBuffers(1, &m_TextureID);
  glad_glActiveTexture(GL_TEXTURE0);

  bind();
  glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB,
                    GL_UNSIGNED_INT, m_Buffer);
  unbind();
}

Texture::Texture(unsigned int w, unsigned int h) : m_Width(w), m_Height(h) {
  clear();
  glad_glGenBuffers(1, &m_TextureID);
  glad_glActiveTexture(GL_TEXTURE0);

  bind();
  glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB,
                    GL_UNSIGNED_INT, m_Buffer);
  unbind();
}

void Texture::bind() { glad_glBindBuffer(GL_TEXTURE_BUFFER, m_TextureID); }

void Texture::unbind() { glad_glBindBuffer(GL_TEXTURE_BUFFER, 0); }

void Texture::clear() { memset(m_Buffer, 0, m_Width * m_Height); }

void Texture::setPixel(unsigned int x, unsigned int y, unsigned int color) {
  if (x <= m_Width && y <= m_Height) {
    m_Buffer[x + y * m_Height] = color;
  }
}

void Texture::flush() {
  bind();
  glad_glTexSubImage2D(GL_TEXTURE_BUFFER, 0, 0, 0, m_Width, m_Height, GL_RGB,
                       GL_UNSIGNED_INT, m_Buffer);
  unbind();
}

Texture::~Texture() {
  glad_glDeleteTextures(1, &m_TextureID);
  delete[] m_Buffer;
}

} // namespace graphics
