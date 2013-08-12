#include <iostream>
#include <TFile.h>

#include "MuonEfficiency/ScaleFactorPlotter.h"

/**
 * Run tests of the ScaleFactorPlotter class
 * @param  argc Number of arguments
 * @param  argv Arguments in char form
 * @return      0 for good, other for bad
 */
int main(int argc, char** argv)
{
  // TFile
  TFile* periodFile = TFile::Open("/home/jblanco/WorkArea/CalibrationWork/RunMakeSF/output/output_2013_08_05_14_55_29_PeriodBNoPRW/TnPFitResults_PeriodBNoPRW.root");

  // Load single histogram for testing
  std::string emptyName = "";
  std::string histoName = "h_data_eta_smt_eff";
  
  // Plotter object
  ScaleFactorPlotter* plotter = new ScaleFactorPlotter("BatchName");

  // Period Struct??
  plotter->Add("PeriodB", periodFile, 46);

  // Draw and save
  plotter->Draw(histoName);

  return (0);
} // End main
