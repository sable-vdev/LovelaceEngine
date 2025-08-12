#version 330 core

layout (location = 0) in vec3 locPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 camera;
uniform vec3 color;
out vec4 outColor;
out vec2 TexCoord;

void main()
{
    gl_Position = camera * model * vec4(locPos, 1.0f);
    outColor = vec4(color, 1.0f);
    TexCoord = aTexCoord;
}