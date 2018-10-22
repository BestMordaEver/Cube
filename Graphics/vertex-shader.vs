#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 vColor;

void main()
{
    gl_Position = projection * view * model * vec4(position.x - 1.5f, position.y - 1.5f, position.z - 1.5f, 1.0f);
    vColor = vertexColor;
}