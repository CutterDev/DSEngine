#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aColor;
layout (location = 4) in mat4 aModel;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	ourColor = aColor;
	TexCoord = aTexCoord;
	gl_Position = projection * view * aModel * vec4(aPos, 1.0f);
}