#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 camera;

out vec2 outTexCoord;
out vec3 outNormal;
out vec3 outFragPos;

void main()
{
    outTexCoord = aTexCoord;
    outFragPos = vec3(model * vec4(aPos, 1.0));
    outNormal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = camera * vec4(outFragPos, 1.0);
}