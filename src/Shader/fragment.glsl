#version 330 core

in vec2 UV

uniform sampler2D sampler;

out vec3 color;
main()
{
  vec3 color = texture(sampler,UV);
}
