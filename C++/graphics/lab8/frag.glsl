#version 330

uniform sampler2D tex;

in vec2 fuv;
in vec3 fcolor;
out vec4 color_out;

void main() {
  //color_out = vec4(fcolor, 1);
  color_out = texture(tex, fuv).rrra;
}
