#version 440
layout(location=0)out vec4 FragColor;
//layout(location=0)in vec2 TexCoord;
//layout(binding=0)uniform sampler2D ourTexture;
void main()
{
    FragColor = vec4(1.0f,1,0,1.0f);// texture(ourTexture,TexCoord);
}
