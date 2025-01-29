#version 150 core

in vec2 position;

out vec2 TexCord;

uniform mat4 trans;

void main() {
    vec2 tc = position;
    tc.x += 0.5;
    TexCord = tc;
    gl_Position = trans * vec4(position, 0.0, 1.0);
}
