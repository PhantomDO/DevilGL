#version 330 core

out vec4 color;

struct Light
{
	vec3 position;
	vec3 ambiant;
	vec3 diffuse;
	vec3 specular;
};

struct Vertex 
{
    vec3 position;
    vec3 normal;
    vec2 uv;
};

in Vertex vertex;

uniform uint texSample = 0u;
uniform sampler2D tex;

#define NB_LIGHTS 2
uniform Light lights[NB_LIGHTS];
uniform uint usedLightCount;

vec3 LightCalculation(Light light, vec3 normal, Vertex vertex)
{
	vec3 uv = texSample == 0u ? vec3(1) : vec3(texture(tex, vertex.uv));

	vec3 ambiant = uv * light.ambiant;

	vec3 direction = normalize(light.position - vertex.position);
	float distance = max(dot(normal, direction), 0);

	vec3 diffuse = uv * distance * light.diffuse;

	vec3 viewDir = normalize(-vertex.position);
	vec3 reflectDir = reflect(-direction, normal);
	float specularValue = pow(max(dot(viewDir, reflectDir), 0), 32);
	vec3 specular = 1.0 * specularValue * light.specular;

	return (ambiant + diffuse + specular);
}

void main()
{
	vec3 normal = normalize(vertex.normal);
	vec3 result = vec3(0);

	for (uint i = 0u; i < usedLightCount; ++i)
	{
		result += LightCalculation(lights[i], normal, vertex);
	}

	color = vec4(result, 1.0);
}
