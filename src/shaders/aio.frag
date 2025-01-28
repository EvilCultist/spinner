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
    float factor1 = (sin(time * PI) + 1.0) / 2.0;
    float factor2 = ((sin(5 + time * 2 * PI) + 1.0) / 2.0);
    if (TexCord.y > 0) {
        vec2 tc = TexCord;
        tc.y = 1 - tc.y;
        // float factor1 = sin(time * PI);
        // float factor2 = ((sin(5 + time * 2 * PI) + 1.0) / 2.0);
        if (tc.x > 0.99 || (tc.x < 0.01) || tc.y > 0.99 || (tc.y < 0.01)) {
            outColor = transparent;
            return;
        }
        // outColor = texture(tex, tc) * vec4(Color, 1.0);
        vec4 mask = texture(texMask, tc) * vec4(Color, 1.0);
        vec4 spinner = texture(texSpinner, tc);
        vec4 glass = texture(texGlass, tc);
        // out1 = mix(glass, mask, time * 1.0);
        vec4 out1 = mix(glass, mask, factor1);
        outColor = mix(out1, spinner, factor2);
        // outColor = texture(tex, tc) * vec4(1.0f, 1.0f, 1.0f, 1.0f);
    } else {
        vec2 tc = TexCord;
        tc.y *= -1;
        tc.y = 1 - tc.y;
        float factor3 = ((sin(1.5 + time * 4 * PI) + 1.0) / 2.0);
        float sinx = 10 * (factor1 + factor2 + factor3) * ((sin(tc.y * mix(4, 10, factor2) * PI) / (5 + factor3 * 10)));
        float cosx = 10 * (factor1 + factor2 + factor3) * ((cos(tc.y * mix(4, 10, factor2) * PI) / (5 + factor3 * 10)));
        float newx = mix(sinx, cosx, tc.x);
        newx *= (0, 10, 1 - tc.y);
        // newx -= floor(newx);
        newx = newx / (mix(5, 20, factor3));
        newx += tc.x;
        if (newx > 0.99 || (newx < 0.01) || tc.y > 0.99 || (tc.y < 0.01)) {
            outColor = transparent;
            return;
        }
        vec2 loc = vec2(newx, tc.y);
        vec4 mask = texture(texMask, loc) * vec4(Color, 1.0);
        vec4 spinner = texture(texSpinner, loc);
        vec4 glass = texture(texGlass, loc);
        // out1 = mix(glass, mask, time * 1.0);
        vec4 out1 = mix(glass, mask, factor1);
        outColor = mix(out1, spinner, factor2);
        // outColor = texture(tex, tc) * vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
}
