#include "Circle.hpp"

Circle::Circle(Transform t, vec3 color)
{
  // Calculates the MVP matrix, it's orthogonal, and we subtract the staring position of the transform
  // to get its world position
  this->Primitive::mvp =
    ortho(-40.0f + t.position.x, 40.0f + t.position.x, -30.0f + t.position.y, 30.0f + t.position.y);

  vec3 tmp = t.scale * vec3(0.5f, 0.5f, 0.5f);

  // Calculates the points of the circle
  float x = .0f;
  for(GLuint i = 0 ; i < verticeBuffer.size() ; i +=3)
	{
    x = i * 2 * 3.1415 / (verticeBuffer.size() - 2);
		verticeBuffer[i] = t.position.x - (tmp.x * cos(x));
		verticeBuffer[i+1] = t.position.y - (tmp.y * sin(x));
	}

  vec3 c = color / vec3(255.f, 255.f, 255.f);
  for(GLuint i = 0; i < verticeColor.size(); i += 3)
  {
    verticeColor[i] = c.x;
    verticeColor[i + 1] = c.y;
    verticeColor[i + 2] = c.z;
  }

  // Move vertex data to video memory; specifically to VBO called vertexbuffer
  glGenBuffers(1, &verticeBufferId);
  // Sets the verticeBufferId with the ID of the generated buffer
  glBindBuffer(GL_ARRAY_BUFFER, verticeBufferId);
  // Create a new data store for the buffer object, using the buffer object currently bound to target.
  glBufferData(GL_ARRAY_BUFFER, verticeBuffer.size() * sizeof(GLfloat), &verticeBuffer.front(), GL_STATIC_DRAW);

  // Move color data to video memory; specifically to CBO called colorbuffer
  glGenBuffers(1, &verticeColorId);
  // Sets the verticeColorId with the ID of the generated buffer
  glBindBuffer(GL_ARRAY_BUFFER, verticeColorId);
  // Create a new data store for the buffer object, using the buffer object currently bound to target.
  glBufferData(GL_ARRAY_BUFFER, verticeColor.size() * sizeof(GLfloat), &verticeColor.front(), GL_STATIC_DRAW);
}

Circle::~Circle()
{
  //Deletes the vertex buffer
  glDeleteBuffers(1, &verticeBufferId);
  //Deletes the color buffer
  glDeleteBuffers(1, &verticeColorId);
}

void Circle::Draw(GLuint shaderId, Transform transform)
{
  // Uses shaderId as our shader
  glUseProgram(shaderId);

  // Gets the mvp position
  unsigned int matrix = glGetUniformLocation(shaderId, "mvp");
  // Passes the matrix to the shader
  glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);
  
  // Creates a translate matrix
  mat4 trans = translate(mat4(1.0f), transform.position);
  // Gets the trans position
  unsigned int t = glGetUniformLocation(shaderId, "trans");
  // Passes the matrix to the shader
  glUniformMatrix4fv(t, 1, GL_FALSE, &trans[0][0]);

  // Creates a rotation matrix
  mat4 rot = rotate(mat4(1), transform.rotation.x, vec3(0, 0, 1));
  // Gets the rot position
  unsigned int r = glGetUniformLocation(shaderId, "rot");
  // Passes the matrix to the shader
  glUniformMatrix4fv(r, 1, GL_FALSE, &rot[0][0]);

  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0);
  // binds verticeBufferId
  glBindBuffer(GL_ARRAY_BUFFER, verticeBufferId);
  // Input 0 of the shader 3 float coordinates
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

  // 2nd attribute buffer : colors
  glEnableVertexAttribArray(1);
  // binds verticeColorId
  glBindBuffer(GL_ARRAY_BUFFER, verticeColorId);
  // Input 1 of the shader 3 float coordinates
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

  // Draws a triangle fan with 60 points
  glDrawArrays(GL_TRIANGLE_FAN, 0, 60);

  // Closes input 0 of the vertex
  glDisableVertexAttribArray(0);
  // Closes input 1 of the vertex
  glDisableVertexAttribArray(1);
}

void Circle::UpdateColor(vec3 color)
{
  // Deletes the old color buffer
  glDeleteBuffers(1, &verticeColorId);
  vec3 c = color / vec3(255.f, 255.f, 255.f);
  
  // loads the new color buffer
  for(GLuint i = 0; i < verticeColor.size(); i += 3)
  {
    verticeColor[i] = c.x;
    verticeColor[i + 1] = c.y;
    verticeColor[i + 2] = c.z;
  }

  // Move color data to video memory; specifically to CBO called colorbuffer
  glGenBuffers(1, &verticeColorId);
  // Sets the verticeColorId with the ID of the generated buffer
  glBindBuffer(GL_ARRAY_BUFFER, verticeColorId);
  // Create a new data store for the buffer object, using the buffer object currently bound to target.
  glBufferData(GL_ARRAY_BUFFER, verticeColor.size() * sizeof(GLfloat), &verticeColor.front(), GL_STATIC_DRAW);
}
