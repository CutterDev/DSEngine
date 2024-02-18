#version 330 core
out vec4 color;

in vec2 TexCoords;
uniform sampler2D tilesheet;

void main()
{
    color = vec4(1.0) * texture(tilesheet, TexCoords);
}