#version 330 core

layout (location = 0) in vec3 position; // the position variable has attribute position 0
layout (location = 1) in vec3 normal; // the normal variable has attribute position 1
layout (location = 2) in vec2 uv; // the uv variable has attribute position 2

struct Vertex 
{
    vec3 position;
    vec3 normal;
    vec2 uv;
};

out Vertex vertex;
uniform mat4 mvp;  
uniform mat4 mv;  

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
    vertex.uv = uv;
    vec4 verticeNormal = transpose(inverse(mv)) * vec4(normal, 0.0);
    vertex.normal = verticeNormal.xyz;
    vec4 verticePosition = mv * vec4(position, 1.0);
    vertex.position = verticePosition.xyz / verticePosition.w;
}     
