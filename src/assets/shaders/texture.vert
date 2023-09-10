#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUV;
layout (location = 3) in int matrixIndexBuffer;

out vec3 normal;
out vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 uMatrices[10];

void main() {
	normal = vertexNormal;
	uv = vertexUV;

	vec3 p = vertexPosition;

	gl_Position = projection * view * model * uMatrices[matrixIndexBuffer] * vec4(p, 1.0);
}
