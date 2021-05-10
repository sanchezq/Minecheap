//change GLSL version according to OpengGl version

#version 450 core

in vec3 FragPos; 
out vec4 FragColor;
in vec3 OurColor;
in vec3 Normal;
in vec2 TexCoord; 

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

uniform Material material;

struct Light {
	vec3 direction;
	float innerCone;
	float outerCone;

	vec4 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	bool is_point;

	float constant;
    float linear;
    float quadratic;
};
#define MAXLIGHTS 10
uniform Light light[MAXLIGHTS];  
uniform int nbrLight;
uniform vec3 viewPos; 
uniform sampler2D ourTexture;

void main()
{
	vec3 result = vec3(0.f, 0.f, 0.f);
	for(int i = 0; i < nbrLight; i++)
	{
		if (light[i].position.w  ==  0.0 )
		{ // directional Light code
		
			/*Ambient*/
			vec3 ambient = light[i].ambient * material.ambient;

			/*Diffuse*/
			vec3 norm = normalize(Normal);
			vec3 lightDir = normalize(-light[i].position.xyz);
			float diff = max(dot(norm, lightDir), 0.0);
			vec3 diffuse = (diff * material.diffuse) * light[i].diffuse;

			/*Specular*/
			vec3 viewDir = normalize(viewPos - FragPos);
			vec3 reflectDir = reflect(-lightDir, norm);  
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
			vec3 specular = light[i].specular;
			result += (ambient + diffuse + specular);
			//FragColor = texture(ourTexture, TexCoord) * vec4(result, 1.0f);
		}
		else  
		{ 
			if(light[i].is_point == true)
			{
				/*Ambient*/
				vec3 ambient = light[i].ambient * material.ambient;

				/*Attenuation*/
				float distance    = length(light[i].position.xyz - FragPos);
				float attenuation = 1.0 / (light[i].constant + light[i].linear * distance + light[i].quadratic * (distance * distance)); 

				/*Diffuse*/
				vec3 norm = normalize(Normal);
				vec3 lightDir = normalize(light[i].position.xyz - FragPos);
				float diff = max(dot(norm, lightDir), 0.0);
				vec3 diffuse = (diff * material.diffuse) * light[i].diffuse;

				/*Specular*/
				vec3 viewDir = normalize(viewPos - FragPos);
				vec3 reflectDir = reflect(-lightDir, norm);  
				float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
				vec3 specular = (material.specular * spec) * light[i].specular;
				
				result += (ambient + diffuse + specular) * attenuation;
			}
			else{
				/*Ambient*/
				vec3 ambient = light[i].ambient * material.ambient;

				/*Attenuation*/
				float distance    = length(light[i].position.xyz - FragPos);
				float attenuation = 1.0 / (light[i].constant + light[i].linear * distance + light[i].quadratic * (distance * distance)); 

				/*Diffuse*/
				vec3 norm = normalize(Normal);
				vec3 lightDir = normalize(light[i].position.xyz - FragPos);
				float diff = max(dot(norm, lightDir), 0.0);
				vec3 diffuse = (diff * material.diffuse) * light[i].diffuse;

				/*Specular*/
				vec3 viewDir = normalize(viewPos - FragPos);
				vec3 reflectDir = reflect(-lightDir, norm);  
				float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
				vec3 specular = (material.specular * spec) * light[i].specular;

				/*SpotLight Test*/
				float theta = dot(lightDir, normalize(-light[i].direction));
				float epsilon = light[i].innerCone - light[i].outerCone;
				float intensity = clamp((theta - light[i].outerCone)/epsilon, 0.0, 1.0);

				
				//FragColor = vec4(0.f, 0.f, 1.f, 1.0f);
				result += (ambient + (diffuse * intensity) + (specular * intensity)) * attenuation;
			}
		}
		FragColor = texture(ourTexture, TexCoord) * vec4(result, 1.0f);
		//FragColor = texture(ourTexture, TexCoord);	
	} 
};