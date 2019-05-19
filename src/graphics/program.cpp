#include "../stdafx.h"

#include "../../vendor/glad/include/glad/glad.h"
#include "../../vendor/glfw3/GLFW/glfw3.h"
#include "program.h"
namespace graphics {

Program::Program(Shader vertexShader, Shader fragmentShader) {
  if (vertexShader.getType() == Vertex &&
      fragmentShader.getType() == Fragment) {
    m_Shaders.emplace_back(vertexShader);
    m_Shaders.emplace_back(fragmentShader);

    m_Program = glad_glCreateProgram();
    if (link()) {
      glad_glUseProgram(m_Program);
    };
  }
}

Program::~Program() { glad_glDeleteProgram(m_Program); }

bool Program::link() {
  for (Shader s : m_Shaders)
    glad_glAttachShader(m_Program, s.getShader());

  glad_glLinkProgram(m_Program);

  int isLinked = 0;
  glGetProgramiv(m_Program, GL_LINK_STATUS, &isLinked);
  if (!isLinked) {
    GLint maxLength = 0;
    glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &maxLength);

    char buffer[maxLength];

    glGetProgramInfoLog(m_Program, maxLength, &maxLength, buffer);
    std::cout << buffer << "\n";

    return false;
  }

  for (Shader s : m_Shaders)
    glad_glDetachShader(m_Program, s.getShader());

  return true;
}
} // namespace graphics
