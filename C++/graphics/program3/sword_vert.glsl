#version 330

uniform mat4 swprojection;
uniform mat4 swview;
uniform mat4 swmodel;

in vec3 swposition;
in vec3 swcolor;
in vec2 swuv;

out vec3 fcolor;
out vec2 fuv;

void main() {
  gl_Position = swprojection * swview * swmodel * vec4(swposition, 1);
  fcolor = swcolor;
  fuv = swuv;
}

