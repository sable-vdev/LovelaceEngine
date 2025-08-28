#version 330 core

out vec4 FragColor;

in vec2 outTexCoord;
in vec3 outNormal;
in vec3 outFragPos;

uniform sampler2D ourTexture;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()
{
    //ambient lightning
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    //diffusion lightning
    vec3 norm = normalize(outNormal);
    vec3 lightDir = normalize(lightPos - outFragPos);
    float diff = max(dot(norm, lightDir), 0.0); 
    // max because we dont want the product to become negative on a 90+ degree angle so the
    // lightning still has effect on vertcies that arent directly shined on by the light
    vec3 diffuse = diff * lightColor;
    
    //specular lightning
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - outFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    //phong result * objectColor
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor =  vec4(result, 1.0);
}