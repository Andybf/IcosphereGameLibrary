#version 330

/* Vertex Shader GLSL 3.30
 * Copyright © 2022 Anderson Bucchianico. All rights reserved.
 */

in vec3 fragColor;
in vec3 outTexCoord;

uniform samplerCube skybox;

out vec4 frag_Color;

void main(void) {
    frag_Color = texture(skybox, outTexCoord);
}
