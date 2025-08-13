#version 460 core

layout(location = 0) in vec3 vertexPosition_pixels;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec3 offset;

out vec4 vertex_color;

void main()
{
    gl_Position = vec4(vertexPosition_pixels + offset, 1.0);
    vertex_color = aColor;
}
