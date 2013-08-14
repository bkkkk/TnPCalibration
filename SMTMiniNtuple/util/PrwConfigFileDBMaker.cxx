#include <iostream>
#include <string>
#include <fstream>

#include <TSystemDirectory.h>
#include <TSystem.h>

#include "SMTMiniNtuple/SkimListMaker.h"
#include "SMTMiniNtuple/SkimListExceptions.h"

int main()
{
  std::string sampleCollectionName = "p1328";

  Skimming::SkimListMaker* listMaker;

  try
  {
    listMaker = new Skimming::SkimListMaker(sampleCollectionName);
  } catch ( const Skimming::cannot_create_file& e ) {
    std::cout << "Could not open file: " << e.filename << std::endl;
    return (1);
  }

  // Trying to get the list of names from the directory is a pain
  // Dont wanna do Regex stuff
  listMaker->Add("NonPromptJPsi", "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/PrwConfig-p1328_NonPromptJPsi-v1.root", "NonPromptJPsi");
  listMaker->Add("PromptJPsi", "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/PrwConfig-p1328_PromptJPsi-v1.root", "PromptJPsi");
  listMaker->Add("PeriodA", "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/LumiCalc-p1328_PeriodA.root", "PeriodA");
  listMaker->Add("PeriodAB", "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/LumiCalc-p1328_PeriodAB-v1.root", "PeriodAB");
  listMaker->Add("PeriodAL", "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/LumiCalc-p1328_PeriodAL-v1.root", "PeriodAL");
  listMaker->Add("PeriodB", "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/LumiCalc-p1328_PeriodB.root", "PeriodB");
  listMaker->Add("PeriodC", "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/LumiCalc-p1328_PeriodC.root", "PeriodC");
  listMaker->Add("PeriodD", "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/LumiCalc-p1328_PeriodD-v1.root", "PeriodD");
  listMaker->Add("PeriodE", "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/LumiCalc-p1328_PeriodE-v1.root", "PeriodE");
  listMaker->Add("PeriodG", "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/LumiCalc-p1328_PeriodG-v1.root", "PeriodG");
  listMaker->Add("PeriodH", "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/LumiCalc-p1328_PeriodH-v1.root", "PeriodH");
  listMaker->Add("PeriodI", "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/LumiCalc-p1328_PeriodI-v1.root", "PeriodI");
  listMaker->Add("PeriodJ", "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/LumiCalc-p1328_PeriodJ-v1.root", "PeriodJ");
  listMaker->Add("PeriodL", "/home/jblanco/WorkArea/CalibrationWork/RootCore/data/PileupReweighting/LumiCalc-p1328_PeriodL-v1.root", "PeriodL");

  listMaker->Write();

  return (0);
};