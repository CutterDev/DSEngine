#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 tileOffset;
out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform float tileSize;

void main()
{
	gl_Position = projection * view * vec4((tileSize * aPos) + tileOffset, 1.0f);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}