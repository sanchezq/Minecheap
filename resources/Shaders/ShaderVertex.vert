//change GLSL version according to OpengGl version

#version 450 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord;

out vec3 OurColor;
out vec3 Normal;
out vec2 TexCoord;
out vec3 FragPos; 


uniform mat4 MVP;
uniform mat4 model;
uniform mat3 normalMatrix;

void main()
{
	gl_Position =  MVP * vec4(aPos, 1.0);
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = normalMatrix * aNormal;  
	OurColor = aColor;
	TexCoord = aTexCoord;
}