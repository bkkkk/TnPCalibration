#include "SMTMiniNtuple/SkimListMaker.h"
#include "SMTMiniNtuple/SkimListExceptions.h"
#include "JacobUtils/LoggingUtility.h"

//______________________________________________________________________________
Skimming::SkimListMaker::
SkimListMaker(const std::string& listName)
 : fListName(listName) 
{
  std::string prefix = "SkimDB-";

  fFilename = prefix + fListName + ".xml";

  fFile = TFile::Open(fFilename.data(), "RECREATE");  

  // Check if file has been created properly
  if(fFile == NULL || fFile->IsZombie() != false)
  {
    throw cannot_create_file(fFilename);
  } 
}

//______________________________________________________________________________
Skimming::SkimListMaker::
~SkimListMaker(void)
{
  fListName = "";
  fFilename = "";
  fFile->Close();
  fFile = NULL;
}

//______________________________________________________________________________
void Skimming::SkimListMaker::
Add(const std::string& name, const std::string& path, const std::string& label)
{
  SkimListItem sample;
  sample.name = name;
  sample.path = path;
  sample.label = label;

  fSkimList.push_back(sample);
}

//______________________________________________________________________________
void Skimming::SkimListMaker::
Write(void)
{
  LOG_INFO() << "Writing to file";

  fFile->WriteObject(&fSkimList, fListName.data());
}

//______________________________________________________________________________
const std::string& Skimming::SkimListMaker::
GetFileName(void) const
{
  return(fFilename);
}

//______________________________________________________________________________
std::string& Skimming::SkimListMaker::
GetFileName(void)
{
  return(fFilename);
}

ClassImp(Skimming::SkimListMaker)
