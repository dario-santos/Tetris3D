#include "Cube.hpp"

Cube::Cube(vec3 color)
{
  this->color = color / vec3(255.f, 255.f, 255.f);
}

std::vector<GLfloat> Cube::verticeBuffer = std::vector<GLfloat>(0);

GLuint Cube::verticeBufferId = 0;

GLuint Cube::cubeVAO = 0;


void Cube::Init()
{
  verticeBuffer =
  {
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

      -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
  };

  // Move vertex data to video memory; specifically to VBO called vertexbuffer
  glGenBuffers(1, &verticeBufferId);
  // Sets the verticeBufferId with the ID of the generated buffer
  glBindBuffer(GL_ARRAY_BUFFER, verticeBufferId);
  // Create a new data store for the buffer object, using the buffer object currently bound to target.
  glBufferData(GL_ARRAY_BUFFER, verticeBuffer.size() * sizeof(GLfloat), &verticeBuffer.front(), GL_STATIC_DRAW);


  glGenVertexArrays(1, &cubeVAO);

  glBindVertexArray(cubeVAO);
}

void Cube::Draw(GLuint shaderId, mat4 model, mat4 view, mat4 projection)
{
  // Uses shaderId as our shader
  glUseProgram(shaderId);

  // Gets the mvp position
  unsigned int m = glGetUniformLocation(shaderId, "model");
  // Passes the matrix to the shader
  glUniformMatrix4fv(m, 1, GL_FALSE, &model[0][0]);

  unsigned int v = glGetUniformLocation(shaderId, "view");
  // Passes the matrix to the shader
  glUniformMatrix4fv(v, 1, GL_FALSE, &view[0][0]);

  unsigned int p = glGetUniformLocation(shaderId, "projection");
  // Passes the matrix to the shader
  glUniformMatrix4fv(p, 1, GL_FALSE, &projection[0][0]);

  // be sure to activate shader when setting uniforms/drawing objects
  glUniform3f(glGetUniformLocation(shaderId, "objectColor"), color.x, color.y, color.z);

  glBindVertexArray(verticeBufferId);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // A cube has 6 sides, each with 6 vertexes -> 6 * 6
  glBindVertexArray(verticeBufferId);
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Closes input 0 of the vertex
  glDisableVertexAttribArray(0);
  // Closes input 1 of the vertex
  glDisableVertexAttribArray(1);
}

void Cube::DrawShading(GLuint shaderId, mat4 model, mat4 view, mat4 projection)
{
  // Uses shaderId as our shader
  glUseProgram(shaderId);

  // Gets the mvp position
  unsigned int m = glGetUniformLocation(shaderId, "model");
  // Passes the matrix to the shader
  glUniformMatrix4fv(m, 1, GL_FALSE, &model[0][0]);

  unsigned int v = glGetUniformLocation(shaderId, "view");
  // Passes the matrix to the shader
  glUniformMatrix4fv(v, 1, GL_FALSE, &view[0][0]);

  unsigned int p = glGetUniformLocation(shaderId, "projection");
  // Passes the matrix to the shader
  glUniformMatrix4fv(p, 1, GL_FALSE, &projection[0][0]);

  // be sure to activate shader when setting uniforms/drawing objects
  glUniform3f(glGetUniformLocation(shaderId, "objectColor"), color.x, color.y, color.z);
  glUniform3f(glGetUniformLocation(shaderId, "lightColor"), 1.0f, 1.0f, 1.0f);
  glUniform3f(glGetUniformLocation(shaderId, "lightPos"), 50.0f, 100.0f, 150.0f);

  glBindVertexArray(verticeBufferId);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // A cube has 6 sides, each with 6 vertexes -> 6 * 6
  glBindVertexArray(verticeBufferId);
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Closes input 0 of the vertex
  glDisableVertexAttribArray(0);
  // Closes input 1 of the vertex
  glDisableVertexAttribArray(1);
}

void Cube::UpdateColor(vec3 color)
{
  this->color = color / vec3(255.f, 255.f, 255.f);
}

vec3 Cube::GetColor()
{
    return this->color;
}
