#version 330 core

// Input
in vec2 TexCoord;

// Output
out vec4 FragColor;

// Bindings
uniform sampler2D textureAtlas;

void main()
{
	FragColor = texelFetch(textureAtlas, ivec2(TexCoord), 0);
}