#pragma once
#include "../stdafx.h"

#include "../../vendor/glfw3/GLFW/glfw3.h"
#include "program.h"
#include "quad.h"
#include "texture.h"

namespace graphics {
#define NESHEIGHT 240
#define NESWIDTH 256

class Screen {
public:
  Screen(unsigned int w, unsigned int h, const std::string &title);
  Screen();

  void Render();
  void setPixel(unsigned int x, unsigned int y, unsigned int color);
  inline unsigned int getWidth() const { return m_Texture.getWidth(); };
  inline unsigned int getHeight() const { return m_Texture.getHeight(); };

private:
  GLFWwindow *m_Window;
  Texture m_Texture;
  Quad m_ScreenRenderer;
  Program m_Program;
};
} // namespace graphics
