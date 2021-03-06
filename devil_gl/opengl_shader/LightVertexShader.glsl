#version 450 core

layout(location = 0) in vec3 position;

uniform mat4 proj;
uniform mat4 model;

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
	mat4 pos = mat4(1);
	pos[3].xyz = light.position;
	gl_Position = proj * pos * model * vec4(position, 1.0);
}