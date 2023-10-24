#version 330 core

layout (location = 0) in float aBlockID;
layout (location = 1) in vec4 aPosition;
layout (location = 2) in vec4 aNormal;
layout (location = 3) in vec4 aUV;


out vec4 vPosition;
out vec4 vNormal;
out vec4 vUV;
out float vBlockID;



uniform mat4 u_View;
uniform mat4 u_Projection;



void main() {

    vPosition = aPosition;
    vNormal = aNormal;
    vUV = aUV;
    vBlockID = aBlockID;


    gl_Position = u_Projection * u_View * aPosition;
}