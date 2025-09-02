#version 330 core

out vec4 FragColor;

in vec2 outTexCoord;
in vec3 outNormal;
in vec3 outFragPos;

//uniform sampler2D ourTexture;
uniform vec3 objectColor;
uniform vec3 cameraPos;

struct Material 
{
    sampler2D diffuse;
    //vec3 ambient;
    //vec3 diffuse;
    sampler2D specular;
    float shininess;
};

struct Light 
{
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
    float cutOff;

    int type;
};

uniform Material material;
uniform Light light;

void main()
{
    vec3 lightDir;
    //directional light
    if(light.type == 0) 
    {
        lightDir = normalize(-light.direction);
    }
    //point light basically 
    else 
    {
        lightDir = normalize(light.position - outFragPos);    
    }

    //ambient lightning
    vec3 ambient = light.ambient * texture(material.diffuse, outTexCoord).rgb;

    //diffusion lightning
    vec3 norm = normalize(outNormal);
    float diff = max(dot(norm, lightDir), 0.0); 
    // max because we dont want the product to become negative on a 90+ degree angle so the
    // lightning still has effect on vertcies that arent directly shined on by the light
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, outTexCoord).rgb;
    
    //specular lightning
    vec3 viewDir = normalize(cameraPos - outFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * light.specular * texture(material.specular, outTexCoord).rgb;

    if(light.type == 1) {
        //pure point light calculations
        //attenuation: basically the strength of point light over time and distance e.g torch making less light on further away objects
        float distance = length(light.position - outFragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

        //phong result
        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
    }
    else if(light.type == 0) 
    {
        //phong result
        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
    }
    else if(light.type == 2) 
    {
        float theta = dot(lightDir, normalize(light.direction));

        if(theta > light.cutOff) 
        {
            float distance = length(light.position - outFragPos);
            float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
            //ambient *= attenuation;
            diffuse *= attenuation;
            specular *= attenuation;

            vec3 result = ambient + diffuse + specular;
            FragColor = vec4(result, 1.0);
        }
        else 
        {
            FragColor = vec4(light.ambient * texture(material.diffuse, outTexCoord).rgb, 1.0);
        }
    }
    
}