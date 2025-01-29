#version 150 core
#define PI 3.1415926538

// uniform vec3 triangleColor;
in vec2 TexCord;

out vec4 outColor;
uniform float time;
uniform sampler2D texSpinner;

vec4 transparent = vec4(
        0.0f,
        0.0f,
        0.0f,
        0.0f
    );

void main() {
    float factor1 = (sin(time * PI) + 1.0) / 2.0;
    float factor2 = ((sin(5 + time * 2 * PI) + 1.0) / 2.0);
    float buf = 0.4;
    if (TexCord.y >= 0) {
        if (TexCord.y <= 0.001 && abs(TexCord.x) < 0.5 + buf && TexCord.x > 0.5 - buf) {
            outColor = vec4(1.0, 1.0, 1.0, 1.0);
            return;
        }
        vec2 tc = TexCord;
        tc.y = 1 - tc.y;
        if (tc.x > 0.99 || (tc.x < 0.01) || tc.y > 0.99 || (tc.y < 0.01)) {
            outColor = transparent;
            return;
        }
        vec4 spinner = texture(texSpinner, tc);
        outColor = spinner;
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
        vec4 spinner = texture(texSpinner, loc);
        outColor = spinner;
    }
}
