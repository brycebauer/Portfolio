#version 330
uniform mat4 projection;
in vec2 position;
in vec3 color;
out vec3 Color;

void main() {
    Color = color;
    gl_Position = projection * vec4(position.x, position.y, 0, 1);
}
