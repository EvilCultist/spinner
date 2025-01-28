#version 150 core

in vec2 position;
in vec3 color;
in vec2 texCord;

out vec3 Color;
out vec2 TexCord;

void main() {
    Color = color;
    // TexCord = texCord;
    vec2 tc = position;
    tc.x += 0.5;
    TexCord = tc;
    gl_Position = vec4(position, 0.0, 1.0);
}
