#version 330 core
layout (points) in;

layout (triangle_strip, max_vertices = 4) out;
out vec2 TexCoords;

in VS_OUT {
    vec4 tex;
    vec4 tex2;
} gs_in[];

void main()
{
    vec4 pos = gl_in[0].gl_Position;
    TexCoords = gs_in[0].tex2.xy;
    gl_Position = pos + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:bottom-left   
    EmitVertex();  

    TexCoords = gs_in[0].tex.zw;
    gl_Position = pos + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:bottom-right
    EmitVertex();

    TexCoords = gs_in[0].tex2.zw;
    gl_Position = pos + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:top-left
    EmitVertex();

    TexCoords = gs_in[0].tex.xy;
    gl_Position = pos + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:top-right
    EmitVertex();
    EndPrimitive();  
}