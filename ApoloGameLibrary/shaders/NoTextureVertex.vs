#version 330

in vec3 positionVec;
in vec3 normals;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 outPosVec;
out vec3 outNormal;

void main() {
    outPosVec = vec3(modelMatrix * vec4(positionVec,1.0));
    outNormal = normals;
    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(positionVec, 1.0);
}
