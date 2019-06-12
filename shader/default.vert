#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;

out vec3 outputColor;

void main()
{
    gl_Position = vec4(vertexPos.x - 0.4, vertexPos.y - 0.4, vertexPos.z, 1.0);
    outputColor = vertexColor;
}