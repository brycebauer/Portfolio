#version 330

uniform mat4 eprojection;
uniform mat4 eview;
uniform mat4 emodel;

in vec3 eposition;
in vec3 ecolor;
in vec2 euv;
in vec3 enormal;

out vec3 fposition;
out vec3 fcolor;
out vec2 fuv;
out vec3 fnormal;

void main() {
  gl_Position = eprojection * eview * emodel * vec4(eposition, 1);
  vec4 tempPosition = (emodel * vec4(eposition,1));
  fposition = tempPosition.xyz;
  vec4 tempNormal = (transpose(inverse(emodel))) * vec4(enormal, 0);
  fnormal = tempNormal.xyz;
  fcolor = ecolor;
  fuv = euv;
}

