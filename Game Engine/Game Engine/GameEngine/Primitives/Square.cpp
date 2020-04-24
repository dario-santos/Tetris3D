#include "Square.hpp"
#include <iostream>

Square::Square(Transform t, vec3 color)
{
    // Calculates the MVP matrix, it's orthogonal, and we subtract the staring position of the transform
    // to get its world position

    this->Primitive::mvp = ortho(-40.0f + t.position.x, 40.0f + t.position.x, -30.0f + t.position.y, 30.0f + t.position.y);

    // Add scale
    // Add translation
    /*this->model = translate(model, t.position);
    this->model = scale(model, t.scale * vec3(0.5f, 0.5f,0.5f));
    vec3 tmp = t.scale * vec3(0.5f, 0.5f, 0.5f);

    std::cout << "MODEL Square: scale    (" << tmp.x << ", " << tmp.y << ", " << tmp.z << ")" <<std::endl;
    std::cout << "              transform(" << t.position.x << ", " << t.position.y << ", " << t.position.z << ")" << std::endl;

    for (int i = 0; i < model.length(); i++)
    {
      for (int j = 0; j < model[i].length(); j++)
        std::cout <<  model[i][j] << " ";
      std::cout << std::endl;
    }


    this->Primitive::mvp *= this->model;
    */

    vec3 c = color / vec3(255.f, 255.f, 255.f);
    for (GLuint i = 0; i < verticeColor.size(); i += 3)
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

Square::~Square()
{
    //Deletes the vertex buffer
    //glDeleteBuffers(1, &verticeBufferId);
    //Deletes the color buffer
    glDeleteBuffers(1, &verticeColorId);
}

std::vector<GLfloat>Square::verticeBuffer = std::vector<GLfloat>(18);
GLuint Square::verticeBufferId = 0;

void Square::Init()
{
  verticeBuffer[0] = -1.0f;
  verticeBuffer[1] = -1.0f;
  verticeBuffer[2] = -1.0f;

  verticeBuffer[3] = -1.0f;
  verticeBuffer[4] = +1.0f;
  verticeBuffer[5] = -1.0f;

  verticeBuffer[6] = +1.0f;
  verticeBuffer[7] = -1.0f;
  verticeBuffer[8] = -1.0f;

  verticeBuffer[9] = -1.0f;
  verticeBuffer[10] = +1.0f;
  verticeBuffer[11] = -1.0f;

  verticeBuffer[12] = +1.0f;
  verticeBuffer[13] = -1.0f;
  verticeBuffer[14] = -1.0f;

  verticeBuffer[15] = +1.0f;
  verticeBuffer[16] = +1.0f;
  verticeBuffer[17] = -1.0f;

  // Move vertex data to video memory; specifically to VBO called vertexbuffer
  glGenBuffers(1, &verticeBufferId);
  // Sets the verticeBufferId with the ID of the generated buffer
  glBindBuffer(GL_ARRAY_BUFFER, verticeBufferId);
  // Create a new data store for the buffer object, using the buffer object currently bound to target.
  glBufferData(GL_ARRAY_BUFFER, verticeBuffer.size() * sizeof(GLfloat), &verticeBuffer.front(), GL_STATIC_DRAW);

}

void Square::Draw(GLuint shaderId, Transform transform)
{
    // Uses shaderId as our shader
    glUseProgram(shaderId);

    mat4 mvp = ortho(-40.0f, 40.0f, -30.0f, 30.0f) * transform.model;

    // Gets the mvp position
    unsigned int matrix = glGetUniformLocation(shaderId, "mvp");
    // Passes the matrix to the shader
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    // binds  verticeBufferId
    glBindBuffer(GL_ARRAY_BUFFER, verticeBufferId);
    // Input 0 of the shader 3 float coordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    // binds verticeColorId
    glBindBuffer(GL_ARRAY_BUFFER, verticeColorId);
    // Input 0 of the shader 3 float coordinates
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Draws 2 triangles, 6 * 3, 6 points with 3 coordinates each 
    glDrawArrays(GL_TRIANGLES, 0, 18);

    // Closes input 0 of the vertex
    glDisableVertexAttribArray(0);
    // Closes input 1 of the vertex
    glDisableVertexAttribArray(1);
}

void Square::UpdateColor(vec3 color)
{
    // Deletes the old color buffer
    glDeleteBuffers(1, &verticeColorId);
    // loads the new color buffer
    vec3 c = color / vec3(255.f, 255.f, 255.f);

    for (GLuint i = 0; i < verticeColor.size(); i += 3)
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
