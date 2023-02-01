#version 330

/* Vertex Shader GLSL 3.30
 * Copyright © 2022 Anderson Bucchianico. All rights reserved.
 */

precision mediump float;

in vec3 outTexCoord;
in float character;

uniform sampler2D texture0;

out vec4 frag_Color;

vec2 processCharacterPosition(float character) {
    float posPixelY = float(int(character/16.0f))*16.0f;
    float xAxisTextureOffset = float(character - posPixelY);
    posPixelY /= 256.0f;
    float posPixelX = (xAxisTextureOffset*16.0f)/256.0f;
    return vec2(posPixelX, posPixelY);
}

void main(void) {
    vec2 charPosition = processCharacterPosition(character);
    vec4 texColor = texture(texture0, vec2(charPosition.x+outTexCoord.x, charPosition.y+outTexCoord.y));
    if (texColor.a < 0.1) {
        discard;
    }
    frag_Color = texColor;
}
