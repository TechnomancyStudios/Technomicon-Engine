#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float time;

const float offset = 1.0f / 600.0f;
const float offset2 = 1.0f / 600.0f;

const float kernal[9] = float[](
        1,1,1,
        1,1,1,
        1,1,1
    );

void main()
{   
    vec4 col = vec4(0.0f);
    
    col += kernal[0] * texture(ourTexture, TexCoord.st + vec2(-offset, offset));
    col += kernal[0] * texture(ourTexture, TexCoord.st + vec2(-offset2, offset2));
    col += kernal[1] * texture(ourTexture, TexCoord.st + vec2(0.0f, offset));
    col += kernal[1] * texture(ourTexture, TexCoord.st + vec2(0.0f, offset2));
    col += kernal[2] * texture(ourTexture, TexCoord.st + vec2(offset, offset));
    col += kernal[2] * texture(ourTexture, TexCoord.st + vec2(offset2, offset2));
    col += kernal[3] * texture(ourTexture, TexCoord.st + vec2(-offset, 0.0f));
    col += kernal[3] * texture(ourTexture, TexCoord.st + vec2(-offset2, 0.0f));
    col += kernal[4] * texture(ourTexture, TexCoord.st + vec2(0.0f, 0.0f));
    col += kernal[4] * texture(ourTexture, TexCoord.st + vec2(0.0f, 0.0f));
    col += kernal[5] * texture(ourTexture, TexCoord.st + vec2(offset, 0.0f));
    col += kernal[5] * texture(ourTexture, TexCoord.st + vec2(offset2, 0.0f));
    col += kernal[6] * texture(ourTexture, TexCoord.st + vec2(-offset, -offset));
    col += kernal[6] * texture(ourTexture, TexCoord.st + vec2(-offset2, -offset2));
    col += kernal[7] * texture(ourTexture, TexCoord.st + vec2(0.0f, -offset));
    col += kernal[7] * texture(ourTexture, TexCoord.st + vec2(0.0f, -offset2));
    col += kernal[8] * texture(ourTexture, TexCoord.st + vec2(offset, -offset));
    col += kernal[8] * texture(ourTexture, TexCoord.st + vec2(offset2, -offset2));
    
    col = col/18.0f;
    
    float average = (col.r+col.g+col.b)/3.0f;
    

    
    
    vec4 tex = texture(ourTexture, vec2(TexCoord.x,TexCoord.y));
    
    
    FragColor = vec4(average,average,average,1.0f);
    BrightColor = tex*vec4(0.0,0.0,0.0,1.0);
}