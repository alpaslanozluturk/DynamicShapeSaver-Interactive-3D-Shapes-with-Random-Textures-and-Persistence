#version 330 core

layout(location = 0) in vec3 aPos; // Pozisyon
layout(location = 1) in vec2 aTexCoord; // Texture koordinatları

out vec2 TexCoords; // Fragment shader için texture koordinatları

uniform mat4 uWorldTransform; // Dünya transform matrisi

void main() {
    gl_Position = uWorldTransform * vec4(aPos, 1.0);
    TexCoords = aTexCoord; // Texture koordinatlarını geç
}
