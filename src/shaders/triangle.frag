#version 150 core

// uniform vec3 triangleColor;
in vec3 Color;
in vec2 texCord;

out vec4 outColor;
uniform sampler2D tex;

void main() {
    outColor = texture(tex, texCord) * vec4(1 - Color, 1.0);
    // outColor = vec4(1 - Color, 1.0);
}
