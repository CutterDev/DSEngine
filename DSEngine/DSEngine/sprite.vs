#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aOffset;
layout (location = 3) in vec3 aColor;
layout (location = 4) in vec2 aScale;
layout (location = 5) in float Rotation;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	ourColor = aColor;
	TexCoord = aTexCoord;
	vec3 offset = 20.0f * aOffset;
	gl_Position = projection * view * vec4((20.0f * aPos) + offset, 1.0f);
}