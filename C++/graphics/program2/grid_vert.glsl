#version 330

uniform mat4 projection;
uniform mat4 view;
uniform mat4 modelGrid;

in vec3 position;

void main() {
  gl_Position = projection * view * modelGrid * vec4(position, 1);
}
