#version 330 core

out vec4 FragColor;
in vec4 outColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec4 lightColor;

void main()
{
    FragColor = outColor;
    FragColor = texture(ourTexture, TexCoord) * outColor * lightColor;
}