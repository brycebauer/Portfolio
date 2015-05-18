#version 330

uniform sampler2D tex;

uniform float diff = .2;
uniform float ambient = .6;
uniform vec3 elightPos = vec3(2.5,0,-6);

in vec3 fpostition;
in vec3 fcolor;
in vec2 fuv;
in vec3 fnormal;

out vec4 color_out;

void main() {
    vec3 l = normalize(elightPos - fpostition);
    float diffuse = diff * dot(l, fnormal);
    color_out = vec4((diffuse + ambient) * texture(tex,fuv).abgr);
//  color_out = vec4(fuv,0,1);
}

