#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float time;

void main()
{   
    float delay = 500;
    vec4 col = vec4( mix(1.0-TexCoord.x, TexCoord.x, cos(time/delay)) ,mix(TexCoord.y, 1.0-TexCoord.y, sin(time/delay)),  mix(TexCoord.x + TexCoord.y, 1.0-(TexCoord.x * TexCoord.y), cos(time/delay)), 1.0f);
    
    vec4 tex = texture(ourTexture, vec2(TexCoord.x,TexCoord.y));
    FragColor = tex*(col*vec4(2.0f));
}