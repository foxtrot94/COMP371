#version 330 core

in vec3 customColor;
//in vec2 textureCoordinates;

out vec4 color;

//uniform sampler2D objectTexture;

void main()
{
    //color = texture(objectTexture,textureCoordinates);
	color = vec4(customColor, 1.0f);
} 