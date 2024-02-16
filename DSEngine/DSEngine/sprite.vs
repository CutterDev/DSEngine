#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>
layout (location = 2) in mat4 instanceMatrix;
out vec2 TexCoords;

// note that we're omitting the view matrix; the view never changes so we basically have an identity view matrix and can therefore omit it.
uniform mat4 projection;

uniform mat4 view;
void main()
{
    TexCoords = vertex.zw;
    gl_Position = projection * view * instanceMatrix * vec4(vertex.xy, 0.0, 1.0);
}