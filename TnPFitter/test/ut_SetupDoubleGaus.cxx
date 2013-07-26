#include "TnPFitter/FitEfficiency.h"

#include "TFile.h"
#include "TH1F.h"

#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char *argv[])
{
  int testStatus = 1;
  
  std::stringstream str;
  str << argv[1];
  int sigma;
  str >> sigma;
  if(sigma == 0) sigma = 3;

  std::string filePathData = "/scratch3/jblanco/CalibrationHistograms/dataSet_2013_07_16_16_51_02_PeriodB/hist-user.jayb88.20130625122121.data12_8TeV.periodB.physics_Muons.PhysCont.NTUP_SMWZ.grp13_v01_p1067.root";
  std::string filePathMC = "/scratch3/jblanco/CalibrationHistograms/dataSet_2013_07_16_16_51_20_PromptJPsi/hist-user.jayb88.mc12_8TeV.208001.Pythia8B_AU2_CTEQ6L1_pp_Jpsimu4mu4.merge.NTUP_SMWZ.e1331_a159_a173_r3549_p1067.root";
  std::string highBkgHistoName = "InvMass_eta_1.10_1.30";
  
  TFile* testDataFile = new TFile(filePathData.c_str(), "OPEN");
  TFile* testMCFile = new TFile(filePathMC.c_str(), "OPEN");
  
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

  double recoEffData = fitEfficiencyData->GetRecoEfficiency();
  double smtEffData = fitEfficiencyData->GetSMTEfficiency();
  
  double recoEffMC = fitEfficiencyMc->GetRecoEfficiency();
  double smtEffMC = fitEfficiencyMc->GetSMTEfficiency();


  std::cout << "Reco efficiency (data)" << recoEffData << std::endl;
  std::cout << "SMT efficiency (data)" << smtEffData << std::endl;

  std::cout << "Reco efficiency (MC)" << recoEffMC << std::endl;
  std::cout << "SMT efficiency (MC)" << smtEffMC << std::endl;

  return testStatus;
}
