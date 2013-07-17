#include <JacobUtils/ReaderTools.h>
/// Logging
#include <JacobUtils/LoggingUtility.h>

#include <iostream>
#include <fstream>
#include <sstream>


namespace RT {

// =============================================================================

std::vector<std::string> GetListFromString(const std::string& inputString)
{
  /// Temp strings and vectors
  std::vector<std::string> list;
  std::string tempString;
  
  /// String stream
  std::stringstream lineStream(inputString);

  // Fill the vector of strings
  while (lineStream >> tempString)
  {
      list.push_back(tempString);
  };

  return list;
};

// =============================================================================

int GetListFromFile(const std::string& path, std::vector<std::string>& elements)
{   
    std::ifstream inputFile(path.c_str());

    if(inputFile.is_open() == 0)
    {
        LOG_ERROR() << "File: " << path << "not found";
        return (0);
    };

    std::string line;

    while(std::getline(inputFile, line))
    {
        std::istringstream in(line);

        std::string element;
        in >> element;

        elements.push_back(element);
    };

    return (1);
};

// =============================================================================

int GetListFromFile(const std::string& path, std::vector<float>& elements)
{   
    std::ifstream inputFile(path.c_str());

    if(inputFile.is_open() == 0)
    {
        LOG_ERROR() << "File: " << path << "not found";
        return (0);
    };

    std::string line;

    while(std::getline(inputFile, line))
    {
        std::istringstream in(line);

        float element;
        in >> element;

        elements.push_back(element);
    };

    return(1);
};

};
