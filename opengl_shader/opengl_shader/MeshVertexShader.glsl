#version 330 core

layout (location = 0) in vec3 position; // the position variable has attribute position 0

uniform mat4 mvp;  

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
}     
