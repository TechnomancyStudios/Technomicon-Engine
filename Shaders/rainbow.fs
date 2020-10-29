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
    vec4 col = vec4( mix(1.0-TexCoord.x, TexCoord.x, cos(time/delay)) ,mix(TexCoord.y, 1.0-TexCoord.y, sin(time/delay)),  mix(TexCoord.x + TexCoord.y, 1.0-(TexCoord.x * TexCoord.y), cos(time/delay)), 1.0f);
    vec4 tex = texture(ourTexture, vec2(TexCoord.x+ 0.05f*cos(TexCoord.y*20.0f +(time/delay)),TexCoord.y));
    vec4 tex2 = texture(ourTexture, vec2(TexCoord.x,TexCoord.y));
    
    float yeet = TexCoord.x + 0.05f*cos(TexCoord.y*20.0f +(time/delay));
    //FragColor = tex*(col*vec4(2.0f));
    
    
    if(yeet >=0.05f && yeet <= 0.95)//0.05 0.95
        FragColor = tex*(col*vec4(2.0f));
    else
        FragColor = vec4(0.0f);
    
    BrightColor = FragColor;

}