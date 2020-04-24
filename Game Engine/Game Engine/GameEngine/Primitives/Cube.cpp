#include "Cube.hpp"

Cube::Cube(Transform t, vec3 color)
{
    // p = 0 0 0
    // s = 2 2 2
    vec3 tmp = t.scale * vec3(0.5f, 0.5f, 0.5f);

    // Primeira face do cubo - face do fundo
    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);

    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);

    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);

    // Segunda face do cubo, Face de c�
    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    // Terceira face do cubo, plano xz, y=0
    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);    // (0,0,0)
    verticeBuffer.push_back(t.position.z - tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);    // (x,0,0)
    verticeBuffer.push_back(t.position.z - tmp.z);

    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);    // (0,0,z)
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);    // (0,0,z)
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);    // (x,0,z)
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);    // (x,0,0)
    verticeBuffer.push_back(t.position.z - tmp.z);

    // Quarta face do cubo, plano xz, y=y
    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);

    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);

    // Quinta face do cubo, plano yz, x=0
    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);

    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);

    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x - tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);

    // Sexta face do cubo, plano yz, x=x
    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y + tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);
    verticeBuffer.push_back(t.position.z + tmp.z);

    verticeBuffer.push_back(t.position.x + tmp.x);
    verticeBuffer.push_back(t.position.y - tmp.y);
    verticeBuffer.push_back(t.position.z - tmp.z);


    vec3 c = color / vec3(255.f, 255.f, 255.f);
    for (GLuint i = 0; i < 18 * 6 ; i += 3)
    {
        verticeColor.push_back(c.x);
        verticeColor.push_back(c.y);
        verticeColor.push_back(c.z);
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

Cube::~Cube()
{
    //Deletes the vertex buffer
    //glDeleteBuffers(1, &verticeBufferId);
    //Deletes the color buffer
    glDeleteBuffers(1, &verticeColorId);
}

void Cube::Draw(GLuint shaderId, mat4 model, mat4 projection)
{
    // Uses shaderId as our shader
    glUseProgram(shaderId);

    mat4 mvp = projection * model;

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

    // A cube has 6 sides, each with 6 vertexes -> 6 * 6
    glDrawArrays(GL_TRIANGLES, 0, 6 * 6);

    // Closes input 0 of the vertex
    glDisableVertexAttribArray(0);
    // Closes input 1 of the vertex
    glDisableVertexAttribArray(1);
}

void Cube::UpdateColor(vec3 color)
{
    // Deletes the old color buffer
    glDeleteBuffers(1, &verticeColorId);
    // loads the new color buffer
    vec3 c = color / vec3(255.f, 255.f, 255.f);

    for (GLuint i = 0; i < verticeColor.size(); i += 3)
    {
        verticeColor.push_back(c.x);
        verticeColor.push_back(c.y);
        verticeColor.push_back(c.z);
    }

    // Move color data to video memory; specifically to CBO called colorbuffer
    glGenBuffers(1, &verticeColorId);
    // Sets the verticeColorId with the ID of the generated buffer
    glBindBuffer(GL_ARRAY_BUFFER, verticeColorId);
    // Create a new data store for the buffer object, using the buffer object currently bound to target.
    glBufferData(GL_ARRAY_BUFFER, verticeColor.size() * sizeof(GLfloat), &verticeColor.front(), GL_STATIC_DRAW);
}
