#include <algorithm>

#include "SMTMiniNtuple/SkimListReader.h"
#include "SMTMiniNtuple/SkimListExceptions.h"

#include <TFile.h>

//______________________________________________________________________________
Skimming::SkimListReader::
SkimListReader(const std::string& filename, const std::string& collection)
: fFileName(filename),
  fCollectionName(collection),
  fSkimList(NULL)
{
  TFile* file = TFile::Open(fFileName.data(), "OPEN");
  if(file == NULL || file->IsZombie() == 1)
  {
    throw cannot_create_file(filename);
  }

  file->GetObject(fCollectionName.data(), fSkimList);
  if(fSkimList == NULL)
  {
    throw collection_not_found(fCollectionName);
  }

  size_t numberOfPeriods = fSkimList->size();
  for(size_t periodIdx = 0; periodIdx != numberOfPeriods; periodIdx++)
  {
    fPeriodList.push_back(fSkimList->at(periodIdx).name);
  }

  if(fPeriodList.size() != numberOfPeriods)
  {
    throw;
  }

  file->Close();
  delete file;
}

//______________________________________________________________________________
Skimming::SkimListReader::
~SkimListReader(void)
{
  fFileName.clear();
  fCollectionName.clear();
  fSkimList = NULL;
  fPeriodList.clear();
}

//______________________________________________________________________________
bool Skimming::SkimListReader::
FindPeriod(const std::string& period)
{
  std::vector<std::string>::const_iterator found = std::find(fPeriodList.begin(),
                                                             fPeriodList.end(),
                                                             period);

  if(found != fPeriodList.end())
  {
    return (true);
  }
  else
  {
    return (false);
  }
}

//______________________________________________________________________________
std::string Skimming::SkimListReader::
GetPeriodPath(const std::string& period)
{
  size_t idx = GetIndexFromName(period);
  return(fSkimList->at(idx).path);
}

//______________________________________________________________________________
std::string Skimming::SkimListReader::
GetPeriodLabel(const std::string& period)
{
  size_t idx = GetIndexFromName(period);
  return(fSkimList->at(idx).label);
} 

//______________________________________________________________________________
const void Skimming::SkimListReader::
ListPeriods(void) const
{
  std::vector<std::string>::const_iterator periodItr = fPeriodList.begin();

  std::cout << "Period available in collection: " << fCollectionName
            << ":" << std::endl;
  for(;periodItr != fPeriodList.end(); periodItr++)
  {
    std::cout << *periodItr << std::endl;
  } 

  return;
}

//______________________________________________________________________________
size_t Skimming::SkimListReader::
GetIndexFromName(const std::string& period)
{
  std::vector<std::string>::const_iterator found = std::find(fPeriodList.begin(),
                                                             fPeriodList.end(),
                                                             period);

  size_t idx = found - fPeriodList.begin();

  return(idx);
}

// 
ClassImp(Skimming::SkimListReader)

