#include "Square.hpp"

Square::Square(vec3 color)
{
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

std::vector<GLfloat>Square::verticeBuffer = std::vector<GLfloat>(0);

GLuint Square::verticeBufferId = 0;

void Square::Init()
{
  verticeBuffer = {
    -.5f, -.5f, -0.5f,
    -.5f, +.5f, -0.5f,
    +.5f, -.5f, -0.5f,
    -.5f, +.5f, -0.5f,
    +.5f, -.5f, -0.5f,
    +.5f, +.5f, -0.5f,
  };

  // Move vertex data to video memory; specifically to VBO called vertexbuffer
  glGenBuffers(1, &verticeBufferId);
  // Sets the verticeBufferId with the ID of the generated buffer
  glBindBuffer(GL_ARRAY_BUFFER, verticeBufferId);
  // Create a new data store for the buffer object, using the buffer object currently bound to target.
  glBufferData(GL_ARRAY_BUFFER, verticeBuffer.size() * sizeof(GLfloat), &verticeBuffer.front(), GL_STATIC_DRAW);
}

void Square::Draw(GLuint shaderId, mat4 mvp)
{
    // Uses shaderId as our shader
    glUseProgram(shaderId);

    unsigned int MVP = glGetUniformLocation(shaderId, "mvp");
    // Passes the matrix to the shader
    glUniformMatrix4fv(MVP, 1, GL_FALSE, &mvp[0][0]);

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
