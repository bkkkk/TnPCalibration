#include <iostream>
#include <string>

#include "SMTMiniNtuple/SkimListReader.h"
#include "SMTMiniNtuple/SkimListExceptions.h"

int main(int argc, char** argv)
{
  std::string filename = argv[1];

  std::string sampleCollectionName = "dummyOutputCollection";

  Skimming::SkimListReader* reader;

  try
  {
    reader = new Skimming::SkimListReader(filename, sampleCollectionName);
  }
  catch (const Skimming::cannot_create_file& e)
  {
    std::cout << "Could not open file: " << e.filename << std::endl;
    return (11);
  }
  catch (const Skimming::collection_not_found& e)
  {
    std::cout << "Could not find collection: " << e.collectionname << std::endl;
    return (12);
  }

  std::string dummyLine = "e34000FGH12";

  bool isPresent = reader->FindPeriod(dummyLine);
  bool shouldNotBePresent = reader->FindPeriod("garbage");

  if(shouldNotBePresent == true)
  {
    std::cout << "Found something it shouldn't have" << std::endl;
    return (10);
  }

  if(isPresent != true)
  {
    std::cout << "Didn't find present object" << std::endl;
    return (11);
  }

  // Print all periods in collection
  reader->ListPeriods();

  std::cout << "Dummy Path" << reader->GetPeriodPath(dummyLine) << std::endl;
  std::cout << "Dummy Label" << reader->GetPeriodLabel(dummyLine) << std::endl;

  return (0);
}