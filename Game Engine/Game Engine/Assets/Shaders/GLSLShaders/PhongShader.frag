#version 330

in vec3 LightIntensity;

layout(location = 0) out vec4 FragColor;

uniform vec3 objectColor;

void main() 
{
    FragColor = vec4(LightIntensity * objectColor, 1.0);
}
