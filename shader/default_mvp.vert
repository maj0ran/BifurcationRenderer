#version 330


layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec3 vertex_color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 outputColor;

void main() {
	gl_Position =  projection * view * model * vec4(vertex_pos, 1.0);
	outputColor = vertex_color;
}
