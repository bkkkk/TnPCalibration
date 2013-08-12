#ifndef SKIMMING_SKIMLIST_H_
#define SKIMMING_SKIMLIST_H_ 1

// C++
#include <vector>
#include <string>
#include "TObject.h"

namespace Skimming {

struct SkimListItem
{
  std::string name;
  std::string path;
  std::string label;

  ClassDef(SkimListItem, 1);
};

typedef std::vector<SkimListItem> SkimList;

}

#endif
