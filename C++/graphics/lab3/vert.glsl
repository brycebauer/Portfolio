#version 330
uniform mat4 projection;
in vec2 position;

void main() {

    gl_Position = projection * vec4(position.x, position.y, 0, 1);
    //uniform gl_Position = mat4(-1 + matrix.x, 1 - matrix.y, 0, 1);
}
