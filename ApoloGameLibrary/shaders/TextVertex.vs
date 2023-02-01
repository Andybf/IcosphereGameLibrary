#version 330

/* Vertex Shader GLSL 3.30
 * Copyright © 2022 Anderson Bucchianico. All rights reserved.
 */

// glGetAttribLocation to get these variables
in vec3 positionVec;
in vec3 texCoord;

// A uniform varialbe dosen't change for every vertex
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform int char[256];
uniform vec2 pos[256];

out vec3 fragColor;
out vec3 outTexCoord;
out float character;

void main(void) {
    vec2 newPosition = vec2(positionVec.x + pos[gl_InstanceID].x, -positionVec.y + pos[gl_InstanceID].y);
    gl_Position = projectionMatrix * modelMatrix * vec4(newPosition, 0.0, 1.0);
    
    outTexCoord = texCoord;
    character = char[gl_InstanceID];
}
