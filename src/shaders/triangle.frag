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

vec4 transparent = vec4(
        0.0f,
        0.0f,
        0.0f,
        0.0f
    );

void main() {
    float factor1 = sin(time * PI);
    float factor2 = ((sin(5 + time * 2 * PI) + 1.0) / 2.0);
    if (TexCord.x > 0.99 || (TexCord.x < 0.01) || TexCord.y > 0.99 || (TexCord.y < 0.01)) {
        outColor = transparent;
        return;
    }
    // outColor = texture(tex, TexCord) * vec4(Color, 1.0);
    vec4 mask = texture(texMask, TexCord) * vec4(Color, 1.0);
    vec4 spinner = texture(texSpinner, TexCord);
    vec4 glass = texture(texGlass, TexCord);
    // out1 = mix(glass, mask, time * 1.0);
    vec4 out1 = mix(glass, mask, factor1);
    outColor = mix(out1, spinner, factor2);
    // outColor = texture(tex, TexCord) * vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
