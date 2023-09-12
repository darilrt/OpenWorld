#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUV;
layout (location = 3) in vec3 vertexColor;

out vec3 normal;
out vec2 uv;
out vec3 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	normal = vertexNormal;
	uv = vertexUV;
	color = vertexColor;

	gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
}
