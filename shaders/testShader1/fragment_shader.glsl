#version 330 core

in vec4 colorByVertex;

out vec4 fragColor;

void main() {
    fragColor = colorByVertex;
}