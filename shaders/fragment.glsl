#version 330 core

in vec2 TexCoords; // Vertex shader'dan gelen texture koordinatları
out vec4 FragColor; // Çıkış rengi

uniform sampler2D texture1; // Texture birimi

void main() {
    FragColor = texture(texture1, TexCoords); // Texture'u kullanarak fragment rengini belirle
}
