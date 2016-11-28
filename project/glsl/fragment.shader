#version 330 core

in vec3 customColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D imageTexture;

void main()
{
    color = texture(imageTexture, TexCoord);
} 