#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    vec4 tex = texture(ourTexture, vec2(TexCoord.x,TexCoord.y));
    
    FragColor = tex;
    BrightColor = tex;
}