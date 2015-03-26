#version 330
in vec3 Color;
out vec4 color_out;

void main() {
    color_out = vec4(Color,1.0);
}
