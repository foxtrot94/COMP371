#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform int NumOfLights; 
uniform vec3 lightpositions[100];



vec3 CalcPointLight(vec3 lightP);

void main()
{
	vec3 result;
   
		 for(int i = 0; i < NumOfLights; i++)
    result += (CalcPointLight(lightpositions[i]) * objectColor);

    color = vec4(result, 1.0f);
} 


vec3 CalcPointLight(vec3 lightP)
{

 // Attenuation
    float distance = length(lightP - FragPos);
    float attenuation = 1.0f / (1.0f + 0.09f * distance + 0.032 * (distance * distance));   

    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
  	
    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightP - FragPos);
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
		
		return(ambient+diffuse+specular);

}