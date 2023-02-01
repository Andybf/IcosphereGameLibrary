#version 330

/* Vertex Shader GLSL 3.30
* Copyright © 2021 Anderson Bucchianico. All rights reserved.
*/

// glGetAttribLocation to get these variables
in vec3 positionVec; // One point (vector) of the model
in vec3 normals;
in vec3 texCoord;

// A uniform varialbe dosen't change for every vertex
uniform mat4 modelMatrix; //one model in the world space
uniform mat4 viewMatrix; // the camera in the world
uniform mat4 projectionMatrix; // projection mode, ortho, perspective

out vec3 fragColor;
out vec3 outTexCoord;

void main(void) {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(positionVec, 1.0);
    fragColor = normals;
    outTexCoord = texCoord;
}
