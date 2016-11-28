#version 330 core

in vec3 customColor;
in vec2 textureCoordinates;

out vec4 color;

uniform sampler2D objectTexture;

void main()
{
	color = texture(objectTexture, textureCoordinates);

	//Fallback if a color is not assigned
	if(color.xyz==vec3(0.f)) {
		color = vec4(customColor, 1.0f);
	}
} 