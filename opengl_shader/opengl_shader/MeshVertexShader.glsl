#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec3 vertexPos;
out vec3 vertexNormal;
out vec2 vertexTexCoord;

uniform mat4 proj;
uniform mat4 model;
uniform mat4 view;

void main() 
{
	gl_Position = proj * view * model * vec4(position, 1.0f);
    vertexTexCoord = texCoord;

	vec4 vNorm4 = transpose(inverse(view * model)) * vec4(normal, 0.0);
	vertexNormal = vNorm4.xyz;

	vec4 vPos4 = view * model * vec4(position, 1.0);
	vertexPos = vPos4.xyz / vPos4.w;
}