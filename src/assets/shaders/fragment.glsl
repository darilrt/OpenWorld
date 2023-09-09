#version 330 core

layout (location = 0) out vec4 fragColor;

in vec3 normal;
in vec2 uv;
in vec3 color;

uniform sampler2D uTexture;

// Directional light from arbitrary direction
vec3 lightDir = normalize(vec3(1.0, 2.0, 1.0));

void main() {
    // Calculate diffuse lighting
    float diffuse = max(dot(normal, lightDir), 0.0);
    // Calculate ambient lighting
    float ambient = 0.305;
    // Calculate final color from diffuse and ambient lighting
    vec3 c = texture(uTexture, uv).rgb * (diffuse + ambient) * color;
    
    fragColor = vec4(c, 1.0);
}