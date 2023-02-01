#version 330

/* Fragment Shader GLSL 3.30
 * Copyright © 2021 Anderson Bucchianico. All rights reserved.
 */

in vec3 fragColor;
in vec3 outTexCoord;

uniform sampler2D texture0;

out vec4 frag_Color;

void main(void) {
    frag_Color = texture(texture0, vec2(outTexCoord)) * vec4(0.75, 0.75, 0.75, 1.0f);
}
