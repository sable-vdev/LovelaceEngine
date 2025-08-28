#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 camera;
uniform mat3 normalMat;

out vec2 outTexCoord;
out vec3 outNormal;
out vec3 outFragPos;

void main()
{
    outTexCoord = aTexCoord;
    outFragPos = vec3(model * vec4(aPos, 1.0));
    //mat3(transpose(inverse(model))) is expensive so i replaced it with a uniform mat that is calculated on the cpu
    outNormal = normalMat * aNormal;
    gl_Position = camera * vec4(outFragPos, 1.0);
}