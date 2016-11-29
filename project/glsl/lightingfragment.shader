#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 textureCoordinates;

uniform vec3 lightPos; 
uniform vec3 lightPos1;
uniform vec3 lightPos2;
uniform vec3 lightPos3;
uniform vec3 lightPos4;
uniform vec3 lightPos5;

uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform sampler2D objectTexture;
uniform vec3 lightdirection; 
uniform float cutoff;
uniform float outtercutoff;



vec3 CalcSpotLight(vec3 lightP);

vec3 CalcPointLight(vec3 lightP);

void main()
{
	vec3 result;
   
	
    result += CalcSpotLight(lightPos);
	result += CalcPointLight(lightPos1);
	result += CalcPointLight(lightPos2);
	result += CalcPointLight(lightPos3);
	result += CalcPointLight(lightPos4);
		result += CalcPointLight(lightPos5);
	color = vec4(result * vec3(texture(objectTexture, textureCoordinates)),1.0f);
    //color = vec4(result, 1.0f);
} 


vec3 CalcSpotLight(vec3 lightP)
{
	vec3 lightDir = normalize(lightP - FragPos);

	
	// Ambient
    float ambientStrength = 0.5f;
    vec3 ambient = ambientStrength * lightColor;
    
   
  	
    // Diffuse 
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
	
	    // Spotlight (soft edges)
    float theta = dot(lightDir, normalize(-lightdirection)); 
    float epsilon = (cutoff- outtercutoff);
    float intensity = clamp((theta - outtercutoff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
	
	// Attenuation
    float distance = length(lightP - FragPos);
    float attenuation = 1.0f / (1.0f + 0.09f * distance + 0.032 * (distance * distance));   

        
		
		ambient*=attenuation;
		diffuse*=attenuation;
		specular*=attenuation;
		
		return(ambient+diffuse+specular);
		

}

vec3 CalcPointLight(vec3 lightP)
{
    // Attenuation
    float distance = length(lightP - FragPos);
    float attenuation = 1.0f / (1.0f + 0.09f * distance + 0.032 * (distance * distance));   

    // Ambient
    float ambientStrength = 100f;
    vec3 ambient = ambientStrength * lightColor;
  	
    // Diffuse 
	vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
		
		ambient*=attenuation;
		diffuse*=attenuation;
		specular*=attenuation;
		
    return (ambient + diffuse + specular);
}