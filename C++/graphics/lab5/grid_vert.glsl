#version 330

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 track;

in vec3 position;

void main() {
  gl_Position = projection * view * model * track * vec4(position, 1);
}
