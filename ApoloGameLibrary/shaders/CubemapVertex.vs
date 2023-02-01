#version 330

/* Vertex Shader GLSL 3.30
 * Copyright © 2022 Anderson Bucchianico. All rights reserved.
 */

in vec3 positionVec;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragColor;
out vec3 outTexCoord;

void main(void) {
    vec4 pos = projectionMatrix * mat4(mat3(viewMatrix)) * modelMatrix * vec4(positionVec, 0.0f);
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
    fragColor = vec3(1,1,1);
    outTexCoord = vec3(positionVec.x, positionVec.y, positionVec.z);
}
