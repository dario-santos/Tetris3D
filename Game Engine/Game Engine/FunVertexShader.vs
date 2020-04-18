#version 330 core

// Input vertex data and color data
layout(location = 0) in vec3 vertexPosition;

// Values that stay constant for the whole mesh.
uniform mat4 mvp;

// Output fragment data
out vec3 fragmentColor;

void main()
{
	// position of each vertex in homogeneous coordinates
	gl_Position = mvp * vec4(vertexPosition, 1.0);

	fragmentColor = vec3(120, 125, 80);
}
