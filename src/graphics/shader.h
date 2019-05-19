#pragma once
#include "../stdafx.h"
namespace graphics {
enum ShaderType { Vertex, Fragment };
class Shader {
public:
  Shader(const std::string &path, ShaderType type);
  ~Shader();
  bool compile(const std::string &path);

  inline const unsigned int getShader() const { return m_Shader; };
  inline const bool m_IsCompiled() const { return m_Compiled; };
  inline const ShaderType getType() const { return m_Type; };

private:
  ShaderType m_Type;
  unsigned int m_Shader;
  bool m_Compiled;
};
} // namespace graphics
