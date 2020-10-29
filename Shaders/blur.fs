#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    float pi = 6.28318530718;
    
    float direction = 32.0;
    float quality = 10.0;
    float size = 2.0;
    
    vec4 col = vec4(0.0);
    
    vec2 radius = vec2(size / direction);
    
    vec4 tex = texture(ourTexture, vec2(TexCoord.x,TexCoord.y));
    

    for(float d = 0.0; d < pi; d+=pi/direction)
    {
        for(float i = 1.0/quality; i <= 1.0; i += 1.0/quality )
        {
            col += texture(ourTexture, TexCoord + vec2(cos(d),sin(d))*radius*i);
        }
    }
    
    col /= quality*direction;
    
    FragColor = col;
    
}