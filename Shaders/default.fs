#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    vec4 tex = texture(ourTexture, vec2(TexCoord.x,TexCoord.y));
    FragColor = tex;
}