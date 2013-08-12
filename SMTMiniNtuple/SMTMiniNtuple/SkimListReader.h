#ifndef SKIMMING_SKIMLISTREADER_H_
#define SKIMMING_SKIMLISTREADER_H_ 1

#include "TObject.h"
#include "SMTMiniNtuple/SkimList.h"
  
#include <string>
#include <vector>

namespace Skimming
{
  class SkimListReader
  {
  public:
    // Ctor
    SkimListReader(const std::string& filename, const std::string& collection);

  public:
    // Dtor
    ~SkimListReader(void);

  public:
    // Find period in collection
    bool FindPeriod(const std::string& period);

  public:
    // Get Period Path
    std::string GetPeriodPath(const std::string& period);

  public:
    // Get Period Label
    std::string GetPeriodLabel(const std::string& period);  

  public:
    // Print periods to screen
    const void ListPeriods(void) const;

  private:
    size_t GetIndexFromName(const std::string& period);


  private:
    std::string fFileName;
    std::string fCollectionName;
    Skimming::SkimList* fSkimList;
    std::vector<std::string> fPeriodList;

    ClassDef(SkimListReader, 1)
  };

}

#endif