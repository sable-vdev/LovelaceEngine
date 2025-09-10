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
#define LIGHT_ARRAY_SIZE 1
uniform Light light[LIGHT_ARRAY_SIZE];

vec3 CalculatePhong(Light l, vec3 norm, vec3 lightDir, vec3 viewDir, float attenuation)
{
    //ambient lightning
    vec3 ambient = l.ambient * texture(material.diffuse, outTexCoord).rgb;

    //diffusion lightning
    float diff = max(dot(norm, lightDir), 0.0); 
    // max because we dont want the product to become negative on a 90+ degree angle so the
    // lightning still has effect on vertcies that arent directly shined on by the light
    vec3 diffuse = l.diffuse * diff * texture(material.diffuse, outTexCoord).rgb;

    //specular lightning
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * l.specular * texture(material.specular, outTexCoord).rgb;
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return vec3(ambient + diffuse + specular);
}

vec3 CalculateDirectionalLight(Light l, vec3 norm, vec3 viewDir)
{
    vec3 lightDir = normalize(-l.direction);

    return CalculatePhong(l, norm, lightDir, viewDir, 1.0);
}

vec3 CalculatePointLight(Light l, vec3 norm, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(l.position - fragPos);

    //pure point light calculations
    //attenuation: basically the strength of point light over time and distance e.g torch making less light on further away objects
    float distance = length(l.position - fragPos);
    float attenuation = 1.0 / (l.constant + l.linear * distance + l.quadratic * (distance * distance));
    
    //phong result
    return CalculatePhong(l, norm, lightDir, viewDir, attenuation);;
}

void main()
{
    vec3 result = vec3(0.0);
    vec3 norm = normalize(outNormal);
    vec3 viewDir = normalize(cameraPos - outFragPos);

    //directional light
    for(int i = 0; i < LIGHT_ARRAY_SIZE; i++) 
    {
        if(light[i].type == 0)
            result += CalculateDirectionalLight(light[i], norm, viewDir);
        //point light basically 
        else result += CalculatePointLight(light[i], norm, outFragPos, viewDir);
    }
    FragColor = vec4(result, 1.0);

    /*
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
    */
}