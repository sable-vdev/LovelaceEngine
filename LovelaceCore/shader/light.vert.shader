#version 330 core

layout (location = 0) in vec3 locPos;

uniform mat4 camera;
uniform mat4 model;
uniform vec4 lightColor;

out vec4 outColor;

void main()
{
    gl_Position = camera * model * vec4(locPos, 1.0);
    outColor = lightColor;
}