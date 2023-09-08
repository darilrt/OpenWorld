#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUV;

out vec3 normal;
out vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	normal = vertexNormal;
	uv = vertexUV;

	gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
}
