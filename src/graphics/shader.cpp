#include "../stdafx.h"

#include "../../vendor/glad/include/glad/glad.h"
#include "../../vendor/glfw3/GLFW/glfw3.h"
#include "shader.h"
namespace graphics {
Shader::Shader(const std::string &path, ShaderType type)
    : m_Type(type), m_Compiled(false) {

  m_Compiled = compile(path);
}

Shader::~Shader() { glad_glDeleteShader(m_Shader); }
bool Shader::compile(const std::string &path) {

  if (m_Compiled)
    glad_glDeleteShader(m_Shader);

  std::ifstream is;
  is.open(path, std::ios::ate | std::ios::binary);

  if (!is.is_open())
    return false;

  unsigned int size = is.tellg();
  is.seekg(0, is.beg);
  std::string shaderCode;
  is.read(&shaderCode[0], size);

  char *strpointer = (char *)shaderCode.c_str();

  switch (m_Type) {
  case Vertex:
    m_Shader = glad_glCreateShader(GL_VERTEX_SHADER);
    break;
  case Fragment:
    m_Shader = glad_glCreateShader(GL_FRAGMENT_SHADER);
    break;
  default:
    break;
  }

  glad_glShaderSource(m_Shader, 1, &strpointer, NULL);

  int compileflag;
  glad_glGetShaderiv(m_Shader, GL_COMPILE_STATUS, &compileflag);
  if (!compileflag) {
    int logSize = 0;
    glGetShaderiv(m_Shader, GL_INFO_LOG_LENGTH, &logSize);
    char buffer[logSize];

    glGetShaderInfoLog(m_Shader, logSize, nullptr, buffer);

    std::cout << buffer << "\n";
    glad_glDeleteShader(m_Shader);
    return false;
  }

  return true;
}

} // namespace graphics
