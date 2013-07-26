#include "TnPFitter/FitterDraw.h"
#include "TnPFitter/FitInterface.h"
#include "TnPFitter/DoubleGausLandauFit.h"
#include <TFile.h>

int main(int argc, char** argv)
{
  std::string filepath = "/scratch3/jblanco/CalibrationHistograms/dataSet_2013_07_16_16_51_02_PeriodB/hist-user.jayb88.20130625122121.data12_8TeV.periodB.physics_Muons.PhysCont.NTUP_SMWZ.grp13_v01_p1067.root";
  std::string highBkgHistoName = "InvMass_eta_1.10_1.30_Probe";
  
  SET_LOG_LEVEL(kINFO);

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

  int sigma = 3;
  int window = 2;  

  DoubleGausLandauFit* fit = new DoubleGausLandauFit("probe", histo, LANDAUFIT::BuildFitConfiguration(histo));
  TNPFITTER::RunFit( fit, sigma, window );

  FitterDraw* draw = new FitterDraw(fit, sigma, window);

  if (draw == NULL)
  {
    std::cout << "Object constructed incorrectly" << std::endl;
    return (1);
  }

  draw->Draw();

  delete draw;

  return 0;
}