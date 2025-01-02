#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec2 aTexOffset;

out vec2 TexCoord;

uniform float atlasHeight;
uniform float tileSize;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = ivec2(
        (aTexCoord.x * 16 + aTexOffset.x), 
        (aTexCoord.y * 16 + aTexOffset.y) + (atlasHeight - tileSize)
    );
}