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
    float factor1 = sin(time * PI);
    // factor1 = 1;
    float factor2 = ((sin(5 + time * 2 * PI) + 1.0) / 2.0);
    // factor2 = 0.5;
    float factor3 = ((sin(1.5 + time * 4 * PI) + 1.0) / 2.0);
    // outColor = texture(tex, TexCord) * vec4(Color, 1.0);
    float newx = (((factor1 + factor2) / 2) + (sin(TexCord.y * mix(4, 10, factor2) * PI) / (5 + factor2 * 10)));
    // newx -= floor(newx);
    newx = newx / (mix(5, 20, factor3));
    newx += TexCord.x;
    newx -= floor(newx);
    vec2 loc = vec2(newx, TexCord.y);
    vec4 mask = texture(texMask, loc) * vec4(Color, 1.0);
    vec4 spinner = texture(texSpinner, loc);
    vec4 glass = texture(texGlass, loc);
    // out1 = mix(glass, mask, time * 1.0);
    vec4 out1 = mix(glass, mask, factor1);
    outColor = mix(out1, spinner, factor2);
    // outColor = texture(tex, TexCord) * vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
