#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float time;

void main()
{   
    float delay = 500;
    
    vec4 tex = texture(ourTexture, vec2(TexCoord.x + 0.05f*cos(TexCoord.y*20.0f),TexCoord.y));
    FragColor = tex;
    BrightColor = tex*vec4(0.0,0.0,0.0,1.0);
}