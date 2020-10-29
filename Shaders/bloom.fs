#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D fragTex;
uniform sampler2D brightTex;

void main()
{
    vec4 frag = texture(fragTex, vec2(TexCoord.x,TexCoord.y));
    vec4 bright = texture(brightTex, vec2(TexCoord.x,TexCoord.y));

    FragColor = frag+bright;
    //BrightColor = bright;
}