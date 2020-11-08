#version 460

layout ( location = 0 ) in vec3 vertex_position;
layout ( location = 1 ) in vec3 vertex_color;
layout ( location = 2 ) in vec3 vertex_texcrood;

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcrood;

void main()
{
	vs_position = vertex_position;
	vs_color = vertex_color;
	vs_texcrood = vec2(vertex_texcrood.x, vertex_texcrood.y*-1.0f);

	gl_Position = vec4(vertex_position, 1.0f);	
}