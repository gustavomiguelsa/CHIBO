#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 main_rotation;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 pos;

void main()
{
    gl_Position = projection * view * pos * main_rotation * model * vec4(aPos, 1.0);
}

