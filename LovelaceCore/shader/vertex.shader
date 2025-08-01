#version 330 core

layout (location = 0) in vec3 locPos;
layout (location = 1) in vec3 locColor;

uniform mat4 model;
uniform mat4 camera;
out vec4 outColor;

void main()
{
    gl_Position = camera * model * vec4(locPos, 1.0f);
    outColor = vec4(locColor, 1.0f);
}