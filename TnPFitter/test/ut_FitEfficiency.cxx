#include <TnPFitter/FitEfficiency.h>
#include <JacobUtils/LoggingUtility.h>

// Root
#include <TH1F.h>
#include <TFile.h>
#include <TCanvas.h>

int main(int argc, char *argv[])
{
  LOG_INFO() << "Testing FitEfficiency";

  std::stringstream str;
  str << argv[1];
  int doDebug;
  str >> doDebug;

  std::string filepath = "/scratch3/jblanco/CalibrationHistograms/dataSet_2013_07_16_16_51_02_PeriodB/";
  std::string filename = "hist-user.jayb88.20130625122121.data12_8TeV.periodB.physics_Muons.PhysCont.NTUP_SMWZ.grp13_v01_p1067.root";
  std::string highBkgHistoName = "InvMass_eta_1.10_1.30";
  
  std::string fullfilepath = filepath + filename;

  TFile* testFile = new TFile(fullfilepath.c_str(), "OPEN");
  if(testFile->IsZombie() == 1)
  {
    LOG_ERROR() << "File could not be opened";
    return (1);
  };

  TH1F* probeHisto = dynamic_cast<TH1F*> (testFile->Get( (highBkgHistoName + "_Probe").c_str() ) );  
  TH1F* muonProbeHisto = dynamic_cast<TH1F*> (testFile->Get( (highBkgHistoName + "_MuonProbe").c_str() ) );
  TH1F* smtHisto = dynamic_cast<TH1F*> (testFile->Get( (highBkgHistoName + "_SMT").c_str() ) );

  if(doDebug != 0) SET_LOG_LEVEL(kINFO);

  FitEfficiency* testEfficiency = new FitEfficiency("test", probeHisto, muonProbeHisto, smtHisto);
  LOG_INFO() << std::endl <<  " === Results === ";
  LOG_INFO() << "Reco Efficiency = " << testEfficiency->GetRecoEfficiency();
  LOG_INFO() << "Reco Error = " << testEfficiency->GetRecoError();
  LOG_INFO() << "SMT Efficiency = " << testEfficiency->GetSMTEfficiency();
  LOG_INFO() << "SMT Error = " << testEfficiency->GetSMTError();
}
