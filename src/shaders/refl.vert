#version 150 core

in vec2 position;
in vec3 color;
in vec2 texCord;

out vec3 Color;
out vec2 TexCord;

void main() {
    Color = color;
    TexCord = texCord;
    gl_Position = vec4(-1 * position, 0.0, 1.0);
}
