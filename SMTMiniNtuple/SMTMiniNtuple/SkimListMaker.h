#ifndef SKIMLIST_SKIMLISTMAKER_H_
#define SKIMLIST_SKIMLISTMAKER_H_ 1

#include <string>

#include "SMTMiniNtuple/SkimList.h"

#include <TFile.h>

/**
 * @class
 *     Makes a list of skims available on disk and writes them to XML file
 */
namespace Skimming {

class SkimListMaker
{

public:
  // Ctor
  SkimListMaker(const std::string& listName = "SkimList");

public:
  // Dtor
  ~SkimListMaker(void);

public:
  // Add samples to the list
  void Add(const std::string&, const std::string& path, const std::string& label);

public:
  // Write the file out to XML
  void Write(void);

public:
  std::string& GetFileName(void);
  const std::string& GetFileName(void) const;

private:
  std::string fListName;
  std::string fFilename;
  TFile* fFile;
  SkimList fSkimList;

  ClassDef(Skimming::SkimListMaker, 1)

}; // End SkimListMaker

} // End namespace Skimming

#endif // ENDIF SKIMLIST_SKIMLISTMAKER_H_