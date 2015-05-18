#version 330

uniform sampler2D tex;

uniform float diff = .1;
uniform float ambient = .5;
uniform vec3 lightPos = vec3(2.5,0,-11);

in vec3 fpostition;
in vec3 fcolor;
in vec2 fuv;
in vec3 fnormal;

out vec4 color_out;

void main() {
    vec3 l = normalize(lightPos - fpostition);
    float diffuse = diff * dot(l, fnormal);
    color_out = vec4((diffuse + ambient) * texture(tex,fuv).abgr);
    //  color_out = vec4(fuv,0,1);
}
