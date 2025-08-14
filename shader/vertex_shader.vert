#version 460 core

layout(location = 0) in vec3 vertexPosition_pixels;
layout(location = 1) in vec4 aColor;

out vec4 vertex_color;

uniform float aspectRatio;
void main()
{
    vec3 pos = vertexPosition_pixels;
    pos.x/= aspectRatio;
    
    gl_Position = vec4(pos, 1.0);
    vertex_color = aColor;
}
