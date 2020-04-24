#include "Circle.hpp"

Circle::Circle(vec3 color)
{
  vec3 c = color / vec3(255.f, 255.f, 255.f);
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

Circle::~Circle()
{
  //Deletes the color buffer
  glDeleteBuffers(1, &verticeColorId);
}

std::vector<GLfloat>Circle::verticeBuffer = std::vector<GLfloat>(180);

GLuint Circle::verticeBufferId = 0;

void Circle::Init()
{
  // Calculates the points of the circle
  float x = .0f;
  for (GLuint i = 0; i < verticeBuffer.size(); i += 3)
  {
    x = ((float)i) * 2.0f * 3.1415f / (verticeBuffer.size() - 2);
    verticeBuffer[i] = cos(x) * 0.5f;
    verticeBuffer[i + 1] = sin(x) * 0.5f;
  }

  // Move vertex data to video memory; specifically to VBO called vertexbuffer
  glGenBuffers(1, &verticeBufferId);
  // Sets the verticeBufferId with the ID of the generated buffer
  glBindBuffer(GL_ARRAY_BUFFER, verticeBufferId);
  // Create a new data store for the buffer object, using the buffer object currently bound to target.
  glBufferData(GL_ARRAY_BUFFER, verticeBuffer.size() * sizeof(GLfloat), &verticeBuffer.front(), GL_STATIC_DRAW);
}

void Circle::Draw(GLuint shaderId, mat4 mvp)
{
  // Uses shaderId as our shader
  glUseProgram(shaderId);

  unsigned int MVP = glGetUniformLocation(shaderId, "mvp");
  // Passes the matrix to the shader
  glUniformMatrix4fv(MVP, 1, GL_FALSE, &mvp[0][0]);

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
