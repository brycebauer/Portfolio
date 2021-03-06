#version 330

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

in vec3 position;
in vec3 color;
in vec3 normal;

out vec3 fcolor;
out vec3 fposition;
out vec3 fnormal;

void main() {
  gl_Position = projection * view * model * vec4(position, 1);
  fcolor = color;
  vec4 tempPosition = (model * vec4(position, 1));
  fposition = tempPosition.xyz;
  vec4 tempNormal = (transpose(inverse(model))) * vec4(normal, 0);
  fnormal = tempNormal.xyz;
}
