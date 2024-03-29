#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D sprite;

void main()
{
    FragColor = texture(sprite, TexCoord)  * vec4(ourColor, 1.0);
}