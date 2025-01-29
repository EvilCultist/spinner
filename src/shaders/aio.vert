#version 150 core

in vec2 position;

out vec2 TexCord;

void main() {
    vec2 tc = position;
    tc.x += 0.5;
    TexCord = tc;
    gl_Position = vec4(position, 0.0, 1.0);
}
