#include "TnPFitter/DoubleGausFit.h"

#include "TFile.h"
#include "TH1F.h"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
  int testStatus = 1;
  
  std::stringstream str;
  str << argv[1];
  int sigma;
  str >> sigma;

  std::string filepath = "/scratch3/jblanco/CalibrationHistograms/dataSet_2013_07_16_16_51_02_PeriodB/hist-user.jayb88.20130625122121.data12_8TeV.periodB.physics_Muons.PhysCont.NTUP_SMWZ.grp13_v01_p1067.root";
  std::string highBkgHistoName = "InvMass_eta_1.10_1.30_Probe";
  
  TFile* testFile = new TFile(filepath.c_str(), "OPEN");
  if(testFile->IsZombie() == 1)
  {
    std::cout << "File could not be opened" << std::endl;
  };

  TH1F* histo = dynamic_cast<TH1F*> (testFile->Get(highBkgHistoName.c_str()));
  
  if(histo == NULL)
  {
    std::cout << "Histograms could not be opened" << std::endl;
  };

  DoubleGausFit* fit = new DoubleGausFit("probe", histo, TNPFITTER::BuildFitConfiguration(histo));
  TNPFITTER::RunFit( fit, sigma, 2 );

  double down = fit->GetBackgroundDownFunction()->GetParameter(0);
  double up = fit->GetBackgroundUpFunction()->GetParameter(0);

  std::cout << "Printing a variable from Up fit: " << up << std::endl;
  std::cout << "Printing a variable from Down fit: " << down << std::endl;

  return testStatus;
}
