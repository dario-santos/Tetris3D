#version 330 core 

in vec3 LightIntensity;
in vec2 TexCoords;

layout(location = 0) out vec4 FragColor;

uniform vec3 objectColor;
uniform sampler2D texture1;

void main() 
{
    FragColor = texture2D(texture1, TexCoords) * vec4(LightIntensity * objectColor, 1.0);
}
