#include "Sin.hpp"

Sin::Sin(Transform t, vec3 color)
{
  // Calculates the MVP matrix, it's orthogonal, and we subtract the staring position of the transform
  // to get its world position
  this->Primitive::mvp =
    ortho(-40.0f + t.position.x, 40.0f + t.position.x, -30.0f + t.position.y, 30.0f + t.position.y);

  // Calculates the points
  int i = 0;
  float y = 0;

  for (float x = -10.f; x < 10.f; x += 2 * 0.25f)
  {
    i = (x + 10.f) / 0.25f;
    y = sin(x);

    verticeBuffer[i] = ((x + t.position.x) / 10.f) * t.scale.x;
    verticeBuffer[i + 1] = (y + t.position.y) * t.scale.y;
  }

  // Move vertex data to video memory; specifically to VBO called vertexbuffer
  glGenBuffers(1, &verticeBufferId);
  // Sets the verticeBufferId with the ID of the generated buffer
  glBindBuffer(GL_ARRAY_BUFFER, verticeBufferId);
  // Create a new data store for the buffer object, using the buffer object currently bound to target.
  glBufferData(GL_ARRAY_BUFFER, verticeBuffer.size() * sizeof(GLfloat), &verticeBuffer.front(), GL_STATIC_DRAW);
}

Sin::~Sin()
{
  //Deletes the vertex buffer
  glDeleteBuffers(1, &verticeBufferId);
}

void Sin::Draw(GLuint shaderId, Transform transform)
{
  glUseProgram(shaderId);

  unsigned int matrix = glGetUniformLocation(shaderId, "mvp");
  glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, verticeBufferId);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glDrawArrays(GL_LINE_STRIP, 0, 40);

  glDisableVertexAttribArray(0);
}

void Sin::UpdateColor(vec3 color) {}
