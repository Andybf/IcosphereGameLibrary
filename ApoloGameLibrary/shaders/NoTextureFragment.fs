#version 330

precision highp float;

in vec3 outNormal;
in vec3 outPosVec;

uniform vec3 lightPosition;

out vec4 frag_Color;

void main() {
    
    vec3 lightColor = vec3(1);
    vec3 objectColor = vec3(0.4f, 0.5f, 0.8f);
    vec3 ambient = 0.1* lightColor;
    
    vec3 lightDirection = normalize(lightPosition - outPosVec);
    float diffuse = max(dot(normalize(outNormal), lightDirection), 0.0);
    vec3 diffuseAmbientCombined = (ambient + diffuse) * objectColor;
    
    frag_Color = vec4(diffuseAmbientCombined * lightColor, 1);
}
