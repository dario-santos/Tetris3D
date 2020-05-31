#version 330 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 tnorm;
out vec4 eyeCoords;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void main()
{
    tnorm = normalize(NormalMatrix * VertexNormal);
    eyeCoords = ModelViewMatrix * vec4(VertexPosition,1.0);
    
    TexCoords = aTexCoords;
    gl_Position = MVP * vec4(VertexPosition,1.0);
}
