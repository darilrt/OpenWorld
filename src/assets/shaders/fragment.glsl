#version 330 core

layout (location = 0) out vec4 fragColor;

in vec3 normal;
in vec2 uv;

uniform sampler2D u_texture;

// Directional light from arbitrary direction
vec3 lightDir = normalize(vec3(1.0, 2.0, 1.0));

void main() {
    // Calculate diffuse lighting
    float diffuse = max(dot(normal, lightDir), 0.0);
    // Calculate ambient lighting
    float ambient = 0.405;
    // Calculate final color from diffuse and ambient lighting
    vec3 color = texture(u_texture, uv).rgb * (diffuse + ambient);
    
    fragColor = vec4(color, 1.0);
}