#version 330

uniform float diff = .1;
uniform float ambient = .5;
uniform vec3 lightPos = vec3(0, 10, 0);

in vec3 fcolor;
in vec3 fnormal;
in vec3 fposition;

out vec4 color_out;

void main() {
  vec3 l = normalize(lightPos - fposition);
  float diffuse = diff * dot(l, fnormal);
  color_out = vec4(((ambient + diffuse) * fcolor), 1);
}
