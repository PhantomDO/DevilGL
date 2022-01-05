#version 450 core

out vec4 color;

struct Light
{
	vec3 position;
	vec3 ambiant;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;

void main()
{
	color = vec4(light.diffuse, 1.0);
}