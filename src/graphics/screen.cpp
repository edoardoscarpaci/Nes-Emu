#include "../stdafx.h"

#include "../../vendor/glad/include/glad/glad.h"
#include "screen.h"
#include "shader.h"
namespace graphics {

Screen::Screen(unsigned int w, unsigned int h, const std::string &title) {

  glfwInit();
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize OpenGL context" << std::endl;
  }
  m_Window = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
  m_Texture = Texture(w, h);
  m_ScreenRenderer = Quad();

  Shader vertexShader("../Shader/vertex.glsl", ShaderType::Vertex);
  Shader fragmentShader("../Shader/fragment.glsl", ShaderType::Fragment);

  m_Program = Program(vertexShader, fragmentShader);
}

void Screen::setPixel(unsigned int x, unsigned int y, unsigned int color) {
  m_Texture.setPixel(x, y, color);
};

void Screen::Render() {
  m_Texture.flush();
  m_Texture.bind();
  m_ScreenRenderer.getVAO().bind();
  m_ScreenRenderer.getIBO().bind();

  glad_glDrawElements(GL_TRIANGLES, m_ScreenRenderer.getIBO().getSize() / 3,
                      GL_UNSIGNED_INT, nullptr);

  m_ScreenRenderer.getVAO().unbind();
  m_ScreenRenderer.getIBO().unbind();
  m_Texture.unbind();
};
} // namespace graphics
