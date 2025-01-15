#version 150 core
#define PI 3.1415926538

// uniform vec3 triangleColor;
in vec3 Color;
in vec2 TexCord;

out vec4 outColor;
uniform float time;
uniform sampler2D texMask;
uniform sampler2D texSpinner;
uniform sampler2D texGlass;

void main() {
    // outColor = texture(tex, TexCord) * vec4(Color, 1.0);
    vec4 mask = texture(texMask, TexCord) * vec4(Color, 1.0);
    vec4 spinner = texture(texSpinner, TexCord);
    vec4 glass = texture(texGlass, TexCord);
    float factor1 = sin(time * PI);
    float factor2 = ((sin(time * 2 * PI) + 1.0) / 2.0);
    // out1 = mix(glass, mask, time * 1.0);
    vec4 out1 = mix(glass, mask, factor1);
    outColor = mix(out1, spinner, factor2);
    // outColor = texture(tex, TexCord) * vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
