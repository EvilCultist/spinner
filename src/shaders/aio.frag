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
    outColor = vec4(Color, 1.0);
    return;
    if (TexCord.x > 0) {
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
    } else {
        float factor1 = (sin(time * PI) + 1.0) / 2.0;
        float factor2 = ((sin(5 + time * 2 * PI) + 1.0) / 2.0);
        float factor3 = ((sin(1.5 + time * 4 * PI) + 1.0) / 2.0);
        float sinx = 10 * (factor1 + factor2 + factor3) * ((sin(TexCord.y * mix(4, 10, factor2) * PI) / (5 + factor3 * 10)));
        float cosx = 10 * (factor1 + factor2 + factor3) * ((cos(TexCord.y * mix(4, 10, factor2) * PI) / (5 + factor3 * 10)));
        float newx = mix(sinx, cosx, TexCord.x);
        newx *= (0, 10, 1 - TexCord.y);
        // newx -= floor(newx);
        newx = newx / (mix(5, 20, factor3));
        newx += TexCord.x;
        if (newx > 0.99 || (newx < 0.01) || TexCord.y > 0.99 || (TexCord.y < 0.01)) {
            outColor = transparent;
            return;
        }
        vec2 loc = vec2(newx, TexCord.y);
        vec4 mask = texture(texMask, loc) * vec4(Color, 1.0);
        vec4 spinner = texture(texSpinner, loc);
        vec4 glass = texture(texGlass, loc);
        // out1 = mix(glass, mask, time * 1.0);
        vec4 out1 = mix(glass, mask, factor1);
        outColor = mix(out1, spinner, factor2);
        // outColor = texture(tex, TexCord) * vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
}
