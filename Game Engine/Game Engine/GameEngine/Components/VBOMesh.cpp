#include "VBOMesh.hpp"

#include <cstdlib>

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <fstream>
using std::ifstream;

#include <sstream>
using std::istringstream;

VBOMesh::VBOMesh(const char* fileName, vec3 color)
{
  loadOBJ(fileName);

  this->color = color;
}

void VBOMesh::Render()
{
  glBindVertexArray(vaoHandle);
  glDrawElements(GL_TRIANGLES, 3 * faces, GL_UNSIGNED_INT, ((GLubyte*)NULL + (0)));
}

void VBOMesh::UpdateColor(vec3 color) 
{
  this->color = color / vec3(255);
}

vec3 VBOMesh::GetColor()
{
  return color * 255.0f;
}

void VBOMesh::loadOBJ(const char* fileName)
{
  vector <vec3> points;
  vector <vec3> normals;
  vector <GLuint> faces;

  int nFaces = 0;

  ifstream objStream(fileName, std::ios::in);

  if (!objStream)
  {
    cerr << "The OBJ file does not exist: " << fileName << endl;
    exit(1);
  }

  string line, token;
  vector<int> face;

  getline(objStream, line);

  while (!objStream.eof())
  {
    // Remove white space
    trimString(line);

    // Ignore empty and comment lines
    if (line.length() > 0 && line.at(0) != '#')
    {
      istringstream lineStream(line);

      lineStream >> token;

      if (token == "v") // Vertice 
      {
        float x, y, z;
        lineStream >> x >> y >> z;

        points.push_back(vec3(x, y, z));
      }
      else if (token == "vn") // Normal
      {
        float x, y, z;
        lineStream >> x >> y >> z;

        normals.push_back(vec3(x, y, z));
      }
      else if (token == "f") // Face
      {
        nFaces++;

        // Process face
        face.clear();
        size_t slash1, slash2;
        while (lineStream.good())
        {
          string vertString;
          lineStream >> vertString;
          int pIndex = -1, nIndex = -1;

          slash1 = vertString.find("/");
          if (slash1 == string::npos)
          {
            pIndex = atoi(vertString.c_str()) - 1;
          }
          else
          {
            slash2 = vertString.find("/", slash1 + 1);
            pIndex = atoi(vertString.substr(0, slash1).c_str()) - 1;
            nIndex = atoi(vertString.substr(slash2 + 1, vertString.length()).c_str()) - 1;
          }

          if (pIndex == -1)
            printf("Missing point index!!!");
          else
            face.push_back(pIndex);

          if (nIndex != -1 && nIndex != pIndex)
            printf("Normal and point indices are not consistent.\n");
        }
        // If number of edges in face is greater than 3,
        // decompose into triangles as a triangle fan.
        if (face.size() > 3)
        {
          int v0 = face[0];
          int v1 = face[1];
          int v2 = face[2];

          // First face
          faces.push_back(v0);
          faces.push_back(v1);
          faces.push_back(v2);

          for (GLuint i = 3; i < face.size(); i++)
          {
            v1 = v2;
            v2 = face[i];
            faces.push_back(v0);
            faces.push_back(v1);
            faces.push_back(v2);
          }
        }
        else
        {
          faces.push_back(face[0]);
          faces.push_back(face[1]);
          faces.push_back(face[2]);
        }
      }
    }
    getline(objStream, line);
  }

  objStream.close();

  // If there are no normals, calculate them
  if(normals.size() == 0)
    generateAveragedNormals(points, normals, faces);

  storeVBO(points, normals, faces);

  cout << "Loaded mesh from: " << fileName << endl;
  cout << " " << points.size() << " points" << endl;
  cout << " " << nFaces << " faces" << endl;
  cout << " " << faces.size() / 3 << " triangles." << endl;
  cout << " " << normals.size() << " normals" << endl;
}

void VBOMesh::generateAveragedNormals(vector<vec3>& points, vector<vec3>& normals, vector<GLuint>& faces)
{
  for(GLuint i = 0; i < points.size(); i++)
    normals.push_back(vec3(0.0f));

  for(GLuint i = 0; i < faces.size(); i += 3) 
  {
    const vec3& p1 = points[faces[i]];
    const vec3& p2 = points[faces[i+1]];
    const vec3& p3 = points[faces[i+2]];

    vec3 a = p2 - p1;
    vec3 b = p3 - p1;
    vec3 n = glm::normalize(glm::cross(a, b));

    normals[faces[i]] += n;
    normals[faces[i+1]] += n;
    normals[faces[i+2]] += n;
  }

  for(GLuint i = 0; i < normals.size(); i++)
    normals[i] = glm::normalize(normals[i]);
}

void VBOMesh::storeVBO(vector<vec3>& points, vector<vec3>& normals, vector<GLuint>& elements)
{
  GLuint nVerts = GLuint(points.size());
  faces = GLuint(elements.size() / 3);

  float* v = new float[3 * nVerts];
  float* n = new float[3 * nVerts];

  unsigned int* el = new unsigned int[elements.size()];

  int idx = 0;
  for (GLuint i = 0; i < nVerts; ++i)
  {
    v[idx] = points[i].x;
    v[idx + 1] = points[i].y;
    v[idx + 2] = points[i].z;

    n[idx] = normals[i].x;
    n[idx + 1] = normals[i].y;
    n[idx + 2] = normals[i].z;

    idx += 3;
  }

  for (unsigned int i = 0; i < elements.size(); i++)
    el[i] = elements[i];

  glGenVertexArrays(1, &vaoHandle);
  glBindVertexArray(vaoHandle);

  int nBuffers = 3;

  GLuint elementBuffer = nBuffers - 1;

  GLuint handle[5];
  GLuint bufIdx = 0;
  glGenBuffers(nBuffers, handle);

  glBindBuffer(GL_ARRAY_BUFFER, handle[bufIdx++]);
  glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), v, GL_STATIC_DRAW);
  glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));
  glEnableVertexAttribArray(0);  // Vertex position

  glBindBuffer(GL_ARRAY_BUFFER, handle[bufIdx++]);
  glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), n, GL_STATIC_DRAW);
  glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));
  glEnableVertexAttribArray(1);  // Vertex normal

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[elementBuffer]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * faces * sizeof(unsigned int), el, GL_STATIC_DRAW);

  glBindVertexArray(0);


  // Clean up
  delete[] v;
  delete[] n;
  delete[] el;
}

void VBOMesh::trimString(string& str)
{
  const char* whiteSpace = " \t\n\r";

  size_t location;

  location = str.find_first_not_of(whiteSpace);
  str.erase(0, location);

  location = str.find_last_not_of(whiteSpace);
  str.erase(location + 1);
}
