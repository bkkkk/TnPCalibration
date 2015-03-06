#include <iostream>
#include <string>
#include <fstream>

#include <TSystemDirectory.h>
#include <TSystem.h>

#include "SMTMiniNtuple/SkimListMaker.h"
#include "SMTMiniNtuple/SkimListExceptions.h"

int main() {
  using SampleAndFilename = std::pair<std::string, std::string>;

  auto sampleCollectionName = "p1328";

  Skimming::SkimListMaker* listMaker;

  try {
    listMaker = new Skimming::SkimListMaker(sampleCollectionName);
  } catch (const Skimming::cannot_create_file& e) {
    std::cout << "Could not open file: " << e.filename << std::endl;
    return (1);
  }

  auto path_prefix = "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/";

  std::vector<SampleAndFilename> samples = {
    {"NonPromptJPsi", "PrwConfig-p1328_NonPromptJPsi-v1.root"},
    {"PromptJPsi", "PrwConfig-p1328_PromptJPsi-v1.root"},
    {"PeriodA", "LumiCalc-p1328_PeriodA.root"},
    {"PeriodAB", "LumiCalc-p1328_PeriodAB-v1.root"},
    {"PeriodAL", "LumiCalc-p1328_PeriodAL-v1.root"},
    {"PeriodB", "LumiCalc-p1328_PeriodB.root"},
    {"PeriodC", "LumiCalc-p1328_PeriodC.root"},
    {"PeriodD", "LumiCalc-p1328_PeriodD-v1.root"},
    {"PeriodE", "LumiCalc-p1328_PeriodE-v1.root"},
    {"PeriodG", "LumiCalc-p1328_PeriodG-v1.root"},
    {"PeriodH", "LumiCalc-p1328_PeriodH-v1.root"},
    {"PeriodI", "LumiCalc-p1328_PeriodI-v1.root"},
    {"PeriodJ", "LumiCalc-p1328_PeriodJ-v1.root"},
    {"PeriodL", "LumiCalc-p1328_PeriodL-v1.root"}
  };

  for(const auto& sample : samples) {
    listMaker->Write(sample.first, path_prefix + sample.second);
  }

  return (0);
}
