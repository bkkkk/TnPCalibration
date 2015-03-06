#ifndef SKIMLIST_SKIMLISTMAKER_H_
#define SKIMLIST_SKIMLISTMAKER_H_ 1

#include <string>

#include "SMTMiniNtuple/SkimList.h"

#include <TFile.h>

namespace Skimming {

class SkimListMaker {

public:
  SkimListMaker(const std::string& listName = "SkimList");
  ~SkimListMaker(void);

  void Add(const std::string&, const std::string& path, const std::string& label);
  void Write();

  std::string GetFileName();
  const std::string GetFileName() const;

private:
  std::string fListName;
  std::string fFilename;
  TFile* fFile;
  SkimList fSkimList;
#ifdef __CINT__
  ClassDef(Skimming::SkimListMaker, 1)
#endif
};

}

#endif
