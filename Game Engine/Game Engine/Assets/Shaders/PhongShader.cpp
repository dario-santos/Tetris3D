#include "./PhongShader.hpp"

PhongShader::PhongShader(Renderer* renderer)
{
  this->renderer = renderer;
}

GLuint PhongShader::texture = 0;
vector<LightSource*> PhongShader::lights = vector<LightSource*>();
GLSLProgram* PhongShader::shader = nullptr;

void PhongShader::Init(const char* texturePath)
{
    texture = Texture::LoadTexture(texturePath);
    lights = Scene::CurrentScene()->GetLigthSources();
    shader = new GLSLProgram();

    try
    {
      shader->compileShader("./Assets/Shaders/GLSLShaders/PhongShader.vert");
      shader->compileShader("./Assets/Shaders/GLSLShaders/PhongShader.frag");

      shader->link();
      shader->use();
    }
    catch (GLSLProgramException& e)
    {
      cerr << e.what() << endl;
      exit(EXIT_FAILURE);
    }
}

void PhongShader::LoadShader(mat4 model, mat4 view, mat4 projection)
{
  //glUseProgram(shader->getHandle());
  shader->use();

  // Set ligts
  shader->setUniform("Light[0].Position", view * lights[0]->position);
  shader->setUniform("Light[0].La", lights[0]->ambiental);
  shader->setUniform("Light[0].Ld", lights[0]->diffuse);
  shader->setUniform("Light[0].Ls", lights[0]->spectral);

  shader->setUniform("Light[1].Position", view * lights[1]->position);
  shader->setUniform("Light[1].La", lights[1]->ambiental);
  shader->setUniform("Light[1].Ld", lights[1]->diffuse);
  shader->setUniform("Light[1].Ls", lights[1]->spectral);


  mat4 mv = view * model;
  shader->setUniform("ModelViewMatrix", mv);
  shader->setUniform("NormalMatrix", mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
  shader->setUniform("MVP", projection * mv);

  // Material
  shader->setUniform("Material.Ka", renderer->GetMaterial()->ambiental);
  shader->setUniform("Material.Kd", renderer->GetMaterial()->diffuse);
  shader->setUniform("Material.Ks", renderer->GetMaterial()->spectral);
  shader->setUniform("Material.Shininess", renderer->GetMaterial()->shininess);

  shader->setUniform("objectColor", (renderer->GetIPrimitive()->GetColor() / vec3(255.f)));
  shader->setUniform("texture1", this->texture);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->texture);

  renderer->Render();

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}


IPrimitive* PhongShader::GetIPrimitive()
{
  return this->renderer->GetIPrimitive();
}

void PhongShader::UpdateShader(const char* texturePath)
{
    this->texture = Texture::LoadTexture(texturePath);
}