#version 150 core

in vec2 position;

out vec2 TexCord;
out mat4 rotation;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vec2 tc = position;
    tc.x += 0.5;
    TexCord = tc;
    gl_Position = projection * view * vec4(position, 0.0, 1.0);
}
