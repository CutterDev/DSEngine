#version 330 core
layout (location = 0) in vec2 pos; // Tex Coords // Top Right, Bottom Right
layout (location = 1) in vec4 tex; // Tex Coords // Top Right, Bottom Right
layout (location = 2) in vec4 tex2; // Tex Coords // Bottom Left, Top Left

// note that we're omitting the view matrix; the view never changes so we basically have an identity view matrix and can therefore omit it.
uniform mat4 projection;

uniform mat4 view;

out VS_OUT {
    vec4 tex;
    vec4 tex2;
} vs_out;

void main()
{
    vs_out.tex = tex;
    vs_out.tex2 = tex2;
    gl_Position = projection * view * vec4(pos, 0.0, 1.0);
}