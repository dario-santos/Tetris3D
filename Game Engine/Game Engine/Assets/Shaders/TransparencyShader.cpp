#include "./TransparencyShader.hpp"

TransparencyShader::TransparencyShader(Renderer* renderer)
{
  this->renderer = renderer;

  try
  {
    shader->compileShader("./Assets/Shaders/GLSLShaders/TransparencyShader.vert");
    shader->compileShader("./Assets/Shaders/GLSLShaders/TransparencyShader.frag");

    shader->link();
    shader->use();
  }
  catch (GLSLProgramException& e)
  {
    cerr << e.what() << endl;
    exit(EXIT_FAILURE);
  }
}

void TransparencyShader::LoadShader(mat4 model, mat4 view, mat4 projection)
{
  // Uses shaderId as our shader
  GLuint shaderId = shader->getHandle();
  glUseProgram(shader->getHandle());

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
  glUniform3f(glGetUniformLocation(shaderId, "objectColor"), renderer->GetIPrimitive()->GetColor().x, renderer->GetIPrimitive()->GetColor().y, renderer->GetIPrimitive()->GetColor().z);

  glEnableVertexAttribArray(0);

  renderer->Render();

  glDisableVertexAttribArray(0);
}

IPrimitive* TransparencyShader::GetIPrimitive()
{
  return this->renderer->GetIPrimitive();
}