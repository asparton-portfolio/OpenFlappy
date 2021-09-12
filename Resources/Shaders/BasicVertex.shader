#version 450 core

layout(location = 0) in vec2 position;

void main()
{
	gl_Position = vec4(position.x, position.y, 0.f, 1.f);
}