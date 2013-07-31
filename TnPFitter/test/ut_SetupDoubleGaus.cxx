#include "TnPFitter/FitEfficiency.h"
#include "JacobUtils/LoggingUtility.h"

#include "TFile.h"
#include "TH1F.h"

#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char *argv[])
{
  SET_LOG_LEVEL(kDEBUG1);

  int testStatus = 1;
  
  std::stringstream str;
  str << argv[1];
  int sigma = 3;
  str >> sigma;
  if(sigma == 0) sigma = 3;
  str.clear();
  str.str(std::string());
  str << argv[2];
  int window = 2;
  str >> window;
  if(window == 0) window = 2;

  std::string filePathData = "/scratch3/jblanco/CalibrationHistograms/dataSet_2013_07_29_14_17_04_Test/hist-user.jayb88.2013062512.periodAB.root";
  std::string filePathMC = "/scratch3/jblanco/CalibrationHistograms/dataSet_2013_07_29_12_43_57_PromptJpsi-PeriodB/hist-user.jayb88.mc12_8TeV.208001.Pythia8B_AU2_CTEQ6L1_pp_Jpsimu4mu4.merge.NTUP_SMWZ.e1331_a159_a173_r3549_p1067.root";
  std::string highBkgHistoName = "InvMass_pt_5000.00_6000.00";
  
  TFile* testDataFile = TFile::Open(filePathData.c_str(), "OPEN");
  TFile* testMCFile = TFile::Open(filePathMC.c_str(), "OPEN");
  
  if(testDataFile->IsZombie() == 1 || testMCFile->IsZombie() == 1)
  {
    std::cout << "File could not be opened" << std::endl;
  };

  TH1F* probeHisto = dynamic_cast<TH1F*> (testDataFile->Get( (highBkgHistoName + "_Probe").c_str() ) );
  TH1F* muonProbeHisto = dynamic_cast<TH1F*> (testDataFile->Get( (highBkgHistoName + "_MuonProbe").c_str() ) );
  TH1F* smtHisto = dynamic_cast<TH1F*> (testDataFile->Get( (highBkgHistoName + "_SMT").c_str() ) );

  TH1F* probeHistoMC = dynamic_cast<TH1F*> (testMCFile->Get( (highBkgHistoName + "_Probe").c_str() ) );
  TH1F* muonProbeHistoMC = dynamic_cast<TH1F*> (testMCFile->Get( (highBkgHistoName + "_MuonProbe").c_str() ) );
  TH1F* smtHistoMC = dynamic_cast<TH1F*> (testMCFile->Get( (highBkgHistoName + "_SMT").c_str() ) );
  
  if(probeHisto == NULL)
  {
    std::cout << "Histograms could not be opened" << std::endl;
    return (1);
  };

  std::cout << "Configuring fitting jobs" << std::endl;
  FitEfficiency* fitEfficiencyData = new FitEfficiency("Data", probeHisto, muonProbeHisto, smtHisto);
  FitEfficiency* fitEfficiencyMc = new FitEfficiency("MC", probeHistoMC, muonProbeHistoMC, smtHistoMC);

  fitEfficiencyData->Draw();
  fitEfficiencyMc->Draw();

  double recoEffData = fitEfficiencyData->GetRecoEfficiency(sigma);
  double smtEffData = fitEfficiencyData->GetSMTEfficiency(sigma);
  double recoEffErrData = fitEfficiencyData->GetRecoError(sigma, window);
  double smtEffErrData = fitEfficiencyData->GetSMTError(sigma, window);

  double recoEffMC = fitEfficiencyMc->GetRecoEfficiency(sigma);
  double smtEffMC = fitEfficiencyMc->GetSMTEfficiency(sigma);
  double recoEffErrMC = fitEfficiencyMc->GetRecoError(sigma, window);
  double smtEffErrMC = fitEfficiencyMc->GetSMTError(sigma, window);


  std::cout << "Reco efficiency (data) " << recoEffData << "+-" << recoEffErrData << std::endl;
  std::cout << "SMT efficiency (data) " << smtEffData << "+-" << smtEffErrData << std::endl;

  std::cout << "Reco efficiency (MC) " << recoEffMC << "+-" << recoEffErrMC << std::endl;
  std::cout << "SMT efficiency (MC) " << smtEffMC << "+-" << smtEffErrMC << std::endl;

  return testStatus;
}
