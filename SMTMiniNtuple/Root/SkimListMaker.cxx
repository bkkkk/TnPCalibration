#include "SMTMiniNtuple/SkimListMaker.h"
#include "SMTMiniNtuple/SkimListExceptions.h"
#include "JacobUtils/LoggingUtility.h"


Skimming::SkimListMaker::SkimListMaker(const std::string& listName)
 : fListName(listName)  {
  auto prefix = "SkimDB-";

  fFilename = prefix + fListName + ".xml";

  fFile = TFile::Open(fFilename.data(), "RECREATE");

  if(fFile || fFile->IsZombie()) {
    throw cannot_create_file(fFilename);
  }
}


Skimming::SkimListMaker::~SkimListMaker() {
  fListName = "";
  fFilename = "";
  delete fFile;
}


void Skimming::SkimListMaker::Add(const std::string& name, const std::string& path, const std::string& label) {
  SkimListItem sample;
  sample.name = name;
  sample.path = path;
  sample.label = label;

  fSkimList.push_back(sample);
}


void Skimming::SkimListMaker::Write() {
  fFile->WriteObject(&fSkimList, fListName.data());
}


const std::string Skimming::SkimListMaker::GetFileName(void) const {
  return(fFilename);
}


std::string Skimming::SkimListMaker::GetFileName(void) {
  return(fFilename);
}

#ifdef __CINT__
ClassImp(Skimming::SkimListMaker)
#endif
