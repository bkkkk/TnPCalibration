#include "TnPFitter/DoubleGausFit.h"
#include "TnPFitter/FitConfig.h"
#include "TnPFitter/FitSetup.h"
#include "Fit/ParameterSettings.h"

#include "TFile.h"
#include "TH1F.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

int main()
{
  int testStatus = 1;

  std::string filepath = "/scratch3/jblanco/CalibrationHistograms/dataSet_2013_05_20_15_07_09_JPsiMCFull/hist-user.jayb88.mc12_8TeV.208001.Pythia8B_AU2_CTEQ6L1_pp_Jpsimu4mu4.merge.NTUP_SMWZ.e1331_a159_a173_r3549_p1067.root";
  std::string highBkgHistoName = "InvMass_pt_0.00_4000.00_eta_-2.00_-1.30";
  
  TFile* testFile = new TFile(filepath.c_str(), "OPEN");
  if(testFile->IsZombie() == 1)
  {
    std::cout << "File could not be opened" << std::endl;
  };

  TH1F* probeHisto = dynamic_cast<TH1F*> (testFile->Get( (highBkgHistoName + "_Probe").c_str() ) );
  TH1F* muonProbeHisto = dynamic_cast<TH1F*> (testFile->Get( (highBkgHistoName+"_MuonProbe").c_str() ) );
  TH1F* smtHisto = dynamic_cast<TH1F*> (testFile->Get( (highBkgHistoName + "_SMT").c_str() ) );
  
  if(probeHisto == NULL)
  {
    std::cout << "Histograms could not be opened" << std::endl;
  };

  std::vector<DoubleGausFit*> fittings;
  fittings.push_back( new DoubleGausFit("probe", probeHisto, TNPFITTER::BuildFitConfiguration(probeHisto) ) );
  fittings.push_back( new DoubleGausFit("muonProbe", muonProbeHisto, TNPFITTER::BuildFitConfiguration(muonProbeHisto) ) );
  fittings.push_back( new DoubleGausFit("smt", smtHisto, TNPFITTER::BuildFitConfiguration(smtHisto) ) );
  
  for(size_t fit = 0; fit != fittings.size(); fit++)
  {
    TNPFITTER::RunFit( fittings[fit] );
  };
  
  return testStatus;
}
