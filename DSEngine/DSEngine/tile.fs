#version 330 core

uniform vec2 aPos;
uniform vec4 aAmbiance;
uniform vec4 aLightColor;
uniform float aDistance;

out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    //float maxD = lightSize + 0.015 * 1;
    float distance = distance(gl_FragCoord.xy, aPos);
    float value = 1.0 - smoothstep(-0.2, aDistance, distance);

    vec4 pixel = texture(ourTexture, TexCoord);
    vec3 ambiance = pixel.rgb * aAmbiance.rgb * aAmbiance.a;
    vec3 light = aLightColor.rgb * aLightColor.a * clamp(value, 0.0, 1.0);

    vec3 intensity = ambiance + light;
    vec3 final = pixel.rgb * intensity;

    FragColor = vec4(final, 1.0);
}