#version 330 core

in vec4 vPosition;
in vec4 vNormal;
in vec4 vUV;
in float vBlockID;

out vec4 FragColor;

uniform sampler2DArray  texArray;


void main() {
    FragColor = texture(texArray, vec3(vUV.xy, vBlockID));
}