#include "Parser.hpp"
#include <sstream>
#include <iostream>

void Parser::ParseFile()
{
  const char config[] = "url=http://example.com\n"
    "file=main.exe\n"
    "true=0";

  std::istringstream is_file(config);

  std::string line;
  while (std::getline(is_file, line))
  {
    std::istringstream is_line(line);
    std::string key;
    if (std::getline(is_line, key, '='))
    {
      std::string value;
      if (std::getline(is_line, value))
        std::cout << "Key: " << key << ", Value: " << value << std::endl;
        // store_line(key, value);
    }
  }
}
