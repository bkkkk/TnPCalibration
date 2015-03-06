#ifndef SKIMMING_SKIMLIST_H_
#define SKIMMING_SKIMLIST_H_ 1

#include <vector>
#include <string>

namespace Skimming {

struct SkimListItem {
  std::string name;
  std::string path;
  std::string label;

#ifdef __CINT__
  ClassDef(SkimListItem, 1);
#endif
};

using SkimList = std::vector<SkimListItem>;

}

#endif
