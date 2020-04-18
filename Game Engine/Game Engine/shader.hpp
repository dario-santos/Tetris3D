/**
 * @file shader.hpp
 *
 * @brief Header do ficheiro shader.cc
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include <GL/glew.h>

/*
 * Function: LoadShaders
 * --------------------------------
 *   Loads vertex and fragment shaders
 *   
 *   vertex_file_path: Path to the vertex shader;
 *   fragment_file_path: Path to the fragment shader; 
 *   
 * return: the shader id.
 */
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
