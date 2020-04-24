#include "Square.hpp"

Square::Square(Transform t, vec3 color)
{
    // Calculates the MVP matrix, it's orthogonal, and we subtract the staring position of the transform
    // to get its world position
    this->Primitive::mvp =
        ortho(-40.0f + t.position.x, 40.0f + t.position.x, -30.0f + t.position.y, 30.0f + t.position.y);

    vec3 tmp = t.scale * vec3(0.5f, 0.5f, 0.5f);
    // Calculates the 6 (two triangles) points of the square
    verticeBuffer[0] = t.position.x - tmp.x;
    verticeBuffer[1] = t.position.y - tmp.y;
    verticeBuffer[2] = t.position.z - tmp.z;

    verticeBuffer[3] = t.position.x - tmp.x;
    verticeBuffer[4] = t.position.y + tmp.y;
    verticeBuffer[5] = t.position.z - tmp.z;

    verticeBuffer[6] = t.position.x + tmp.x;
    verticeBuffer[7] = t.position.y - tmp.y;
    verticeBuffer[8] = t.position.z - tmp.z;

    verticeBuffer[9] = t.position.x - tmp.x;
    verticeBuffer[10] = t.position.y + tmp.y;
    verticeBuffer[11] = t.position.z - tmp.z;

    verticeBuffer[12] = t.position.x + tmp.x;
    verticeBuffer[13] = t.position.y - tmp.y;
    verticeBuffer[14] = t.position.z - tmp.z;

    verticeBuffer[15] = t.position.x + tmp.x;
    verticeBuffer[16] = t.position.y + tmp.y;
    verticeBuffer[17] = t.position.z - tmp.z;

    vec3 c = color / vec3(255.f, 255.f, 255.f);
    for (GLuint i = 0; i < verticeColor.size(); i += 3)
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

Square::~Square()
{
    //Deletes the vertex buffer
    glDeleteBuffers(1, &verticeBufferId);
    //Deletes the color buffer
    glDeleteBuffers(1, &verticeColorId);
}

void Square::Draw(GLuint shaderId, Transform transform)
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
    unsigned int m = glGetUniformLocation(shaderId, "trans");
    // Passes the matrix to the shader
    glUniformMatrix4fv(m, 1, GL_FALSE, &trans[0][0]);

    // Creates a rotation matrix
    mat4 rot = rotate(mat4(1), transform.rotation.x, glm::vec3(0, 0, 1));
    // Gets the rot position
    unsigned int r = glGetUniformLocation(shaderId, "rot");
    // Passes the matrix to the shader
    glUniformMatrix4fv(r, 1, GL_FALSE, &rot[0][0]);

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