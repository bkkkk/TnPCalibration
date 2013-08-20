#include "TnPFitter/HybridGausFit.h"

#include "TFile.h"
#include "TH1F.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main(int argc, char *argv[])
{
  std::stringstream str;

  str << argv[1];
  int sigma = 3;
  str >> sigma;

  str.clear();
  str.str(std::string());
  str << argv[2];
  int window = 2;
  str >> window;
  str << argv[3];
  std::string bin = "eta_-0.10_0.00";
  str >> bin;

  std::string filepath = "./hist-user.test.root";
  std::stringstream inputHistoName;
  inputHistoName << "InvMass_" << bin;
  std::string lowBkgHistoName = inputHistoName.str() + "_MuonProbe";
  std::string highBkgHistoName = inputHistoName.str() + "_Probe";

  TFile* testFile = new TFile(filepath.c_str(), "OPEN");
  if(testFile->IsZombie() == 1)
  {
    std::cout << "File could not be opened" << std::endl;
  };

  TH1F* highBkgHisto = dynamic_cast<TH1F*> (testFile->Get(highBkgHistoName.c_str()));
  TH1F* lowBkgHisto = dynamic_cast<TH1F*> (testFile->Get(lowBkgHistoName.c_str()));
  if(highBkgHisto == NULL || lowBkgHisto == NULL)
  {
    std::cout << "Histograms could not be opened" << std::endl;
  };

  HybridGausFit* lowFit = new HybridGausFit("muonprobe", lowBkgHisto, TNPFITTER::BuildHybridGausFitConfiguration(histo));
  TNPFITTER::RunFit( lowFit );
  TNPFITTER::DrawFit( lowFit, sigma, window );

  HybridGausFit* highFit = new HybridGausFit("probe", highBkgHisto, TNPFITTER::BuildHybridGausFitConfiguration(histo));
  TNPFITTER::RunFit( highFit );
  TNPFITTER::DrawFit( highFit, sigma, window );

  double lowUp = lowFit->GetBackgroundUpFunction()->GetParameter(0);
  double highUp = highFit->GetBackgroundUpFunction()->GetParameter(0);

  std::cout << "Printing a variable from Up fit of low: " << lowUp << std::endl;
  std::cout << "Printing a variable from Up fit of high: " << highUp << std::endl;
}
