#include <iostream>
#include <string>
#include <fstream>

#include "SMTMiniNtuple/SkimListMaker.h"
#include "SMTMiniNtuple/SkimListExceptions.h"

// Tests the writing functions of the SkimListMaker
// SkimListMaker should be able to write an XML file with a list of samples
// Searching for a dummy string then lets you see if things worked well
int main()
{
  std::string sampleCollectionName = "dummyOutputCollection";
  
  Skimming::SkimListMaker* listMaker;

  try
  {
    listMaker = new Skimming::SkimListMaker(sampleCollectionName);
  } catch ( const Skimming::cannot_create_file& e ) {
    std::cout << "Could not open file: " << e.filename << std::endl;
    return (1);
  }
  
  // Create a dummy string to be added to the XML file
  std::string dummyLine = "e34000FGH12";

  listMaker->Add(dummyLine, "dummyPath", "dummyLabel");
  listMaker->Write();

  std::string fileName = listMaker->GetFileName();
  std::cout << "Filename: " << fileName << std::endl;

  std::ifstream inFile(fileName.data());

  std::string line;

  delete listMaker;

  std::cout << "All is well" << std::endl;

  return (0);
};
