#include <iostream>

#include "JacobUtils/SampleList.h"

#include "TFile.h"

ST::SampleList::SampleList(const std::string& path) : dataset(NULL) {
  dataset = TFile::Open(path.c_str(), "UPDATE");

  std::cout << "Openning file: " << path << std::endl;

  dataset->GetObject("sampleMap", sampleMap);
  if (sampleMap == NULL) {
    std::cout << "Failed to get dataset object. Creating a new one"
              << std::endl;
    sampleMap = new SampleMap;
  }
}

ST::SampleList::SampleList(TFile* file) : dataset(file), sampleMap(NULL) {
  if (dataset == NULL || dataset->IsZombie() == true) {
    std::cerr << "File not found" << std::endl;
    throw;
  }

  dataset->GetObject("sampleMap", sampleMap);
  if (sampleMap == NULL) {
    std::cout << "Failed to get dataset object. Creating a new one"
              << std::endl;
    sampleMap = new SampleMap;
  }
}

ST::SampleList::~SampleList() {
  dataset->Close();
  delete dataset;
}

std::string ST::SampleList::GetPath(const std::string& name) {
  if (IsPresent(name) == false)
    return ("");

  return ((*sampleMap)[name]);
}

void ST::SampleList::AddSample(const std::string& name,
                               const std::string& path) {
  if (IsPresent(name)) {
    std::cout << "Entry: " << name << " already in list, updating path";
  }

  (*sampleMap)[name] = path;
}

void ST::SampleList::RemoveSample(const std::string& name) {
  if (IsPresent(name) == false)
    return;

  int removed = sampleMap->erase(name);

  if (removed == 1) {
    std::cout << "Element: " << name << " successfully removed" << std::endl;
  } else {
    std::cout << "Element " << name << " not found " << std::endl;
  }
}

void ST::SampleList::Write(void) {
  dataset->WriteObject(sampleMap, "sampleMap");
}

void ST::SampleList::Print(void) {
  SampleMap::iterator itr = sampleMap->begin();
  for (; itr != sampleMap->end(); itr++) {
    std::cout << "Name: " << (*itr).first << ", Path: " << (*itr).second
              << std::endl;
  }
}

#ifdef __CINT__
ClassImp(ST::SampleList)
#endif
