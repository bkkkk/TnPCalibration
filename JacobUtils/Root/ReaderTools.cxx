// C++
#include <iostream>
#include <fstream>
#include <sstream>

/// Logging
#include "JacobUtils/LoggingUtility.h"
#include <TFile.h>

#include "JacobUtils/ReaderTools.h"

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

void GetListFromFile(const std::string& path, std::vector<std::string>& elements)
{   
  std::ifstream inputFile(path.c_str());

  if(inputFile.is_open() == 0)
  {
    LOG_ERROR() << "File: " << path << "not found";
    throw;
  };

  std::string line;

  while(std::getline(inputFile, line))
  {
    std::istringstream in(line);

    std::string element;
    in >> element;

    elements.push_back(element);
  };
};

// =============================================================================

void GetListFromFile(const std::string& path, std::vector<float>& elements)
{   
  std::ifstream inputFile(path.c_str());

  if(inputFile.is_open() == 0)
  {
    LOG_ERROR() << "File: " << path << "not found";
    throw;
  };

  std::string line;

  while(std::getline(inputFile, line))
  {
    std::istringstream in(line);

    float element;
    in >> element;

    elements.push_back(element);
  };
};

// =============================================================================

std::vector<std::string> GetListFromXML(const std::string& inputFilePath,
                                         const std::string& listName)
{
  TFile* inputFile = TFile::Open(inputFilePath.data());

  if(inputFile == NULL || inputFile->IsZombie() == false)
  {
    LOG_ERROR() << "ReaderTools :: Failed to open file: " << inputFilePath;
    throw;
  };

  std::vector<std::string>* vectorPtr;

  inputFile->GetObject(listName.data(), vectorPtr);
  if(vectorPtr == NULL)
  {
    LOG_ERROR() << "ReaderTools :: Vector not filled properly";
    throw;
  }
  return (*vectorPtr);
};

// =============================================================================
std::string GetStringFromFileXML(const std::string& inputFile,
                                 const std::string& listName)
{
  std::vector<std::string> vector = RT::GetListFromXML(inputFile, listName);

  // Avoid looping if vector is empty
  if(vector.size() == 0)
  {
    LOG_WARNING() << "There are no elements in this list";
    return("");
  };

  // @todo add custom separator support
  std::string separatror = ",";
  std::stringstream tempStr;


  std::vector<std::string>::iterator itr = vector.begin();

  // Need to add the first element myself to avoid having a comma after
  // the last element in the string list
  tempStr << (*itr);
  itr++;

  // Add the spearator and then the next item on the list
  for(;itr != vector.end(); itr++)
  {
    tempStr << separatror << (*itr);
  }

  return(tempStr.str());
}

}; // END NAMESPACE RT
