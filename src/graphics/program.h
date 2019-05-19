#pragma once
#include "../stdafx.h"
#include "shader.h"
namespace graphics {
class Program {
public:
  Program(Shader vertexShader, Shader fragmentShader);
  Program();
  ~Program();

private:
  std::vector<Shader> m_Shaders;
  unsigned int m_Program;

  bool link();
};
} // namespace graphics
