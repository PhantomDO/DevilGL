#version 330 core

out vec4 color;

struct sLight
{
	vec3 position;
	vec3 ambiant;
	vec3 diffus;
	vec3 specular;
};

in vec3 vertexPos;
in vec3 vertexNormal;
in vec2 vertexTexCoord;

uniform sampler2D theTexture;

#define NB_LIGHTS 2
uniform sLight light[NB_LIGHTS];
uniform uint nbUsedLight;

vec3 CalculLight(sLight light, vec3 normal, vec3 vertexPos);

void main()
{
	vec3 normal = normalize(vertexNormal);
	vec3 result = vec3(0);
	for(uint i=0u; i < nbUsedLight; ++i)
		result += CalculLight(light[i], normal, vertexPos);
	color = vec4(result, 1.0);
}

vec3 CalculLight(sLight light, vec3 normal, vec3 vertexPos)
{
	vec3 objectAmbiant = vec3(texture(theTexture, vertexTexCoord)) * light.ambiant;
	
	vec3 lightdir = normalize(light.position - vertexPos);
	float diff = max(dot(normal, lightdir), 0.0);
	vec3 objectDiffus = vec3(texture(theTexture, vertexTexCoord)) * diff * light.diffus;

	vec3 viewdir = normalize(- vertexPos);
	vec3 reflectdir = reflect(-lightdir, normal);
	float spec = pow(max(dot(viewdir, reflectdir), 0.0), 32);
	vec3 objectSpec = 1.0 * spec * light.specular;

	return (objectAmbiant + objectDiffus + objectSpec);
}