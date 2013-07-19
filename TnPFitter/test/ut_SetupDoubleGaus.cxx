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
#include <sstream>

int main(int argc, char *argv[])
{
  int testStatus = 1;
  
  std::stringstream str;
  str << argv[1];
  int sigma;
  str >> sigma;

  std::string filepath = "/scratch3/jblanco/CalibrationHistograms/dataSet_2013_07_16_16_51_20_PromptJPsi/hist-user.jayb88.mc12_8TeV.208001.Pythia8B_AU2_CTEQ6L1_pp_Jpsimu4mu4.merge.NTUP_SMWZ.e1331_a159_a173_r3549_p1067.root";
  std::string highBkgHistoName = "InvMass_pt_5000.00_6000.00_eta_-2.00_-1.30";
  
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
  
  std::vector<double> yield;

  std::cout << "Sigma to integrate: " << sigma << std::endl;

  for(size_t fit = 0; fit != fittings.size(); fit++)
  {
    TNPFITTER::RunFit( fittings[fit] );
    std::cout << "Signal yield: " << fittings[fit]->GetSignalIntegral(sigma) << std::endl;
    std::cout << "Background yield: " << fittings[fit]->GetBackgroundIntegral(sigma) << std::endl;
    yield.push_back(fittings[fit]->GetSignalIntegral(sigma));
  };

  std::cout << "Reco efficiency " << yield.at(1)/yield.at(0) << std::endl;
  std::cout << "SMT efficiency " << yield.at(2)/yield.at(1) << std::endl;

  return testStatus;
}
