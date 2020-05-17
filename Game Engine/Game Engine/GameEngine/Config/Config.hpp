/*********************************************************************
 * \file   Config.hpp
 * \brief  Config class, parses the config file(s)
 *
 * \author Dário Santos
 * \date   April 2020
***********************************************************************/
#pragma once

#include <map>
#include <string>
#include <fstream>
#include <sstream>

#include "../Input/Input.hpp"

using namespace std;

/**
 * Config
 */
class Config
{
private:
  Config() = default;
  ~Config() = default;

public:
  /** Map from section to (key, value) */
  static map<string, map<string, int>> keys;
  
  /**
   * LoadConfig
   *
   * \param path The path of the file that will be parsed
   */
  static void LoadConfig(char const* path);
};
