#version 330 core

out vec4 FragColor;
in vec4 outColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    //FragColor = outColor;
    FragColor = texture(ourTexture, TexCoord);
}