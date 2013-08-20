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
  int sigma = 3;
  str >> sigma;

  str.clear();
  str.str(std::string());
  str << argv[2];
  int window = 2;
  str >> window;

  std::string filepath = "./hist-user.test.root";
  std::string highBkgHistoName = "InvMass_eta_2.00_2.50_Probe";
  
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
  TNPFITTER::RunFit( fit );
  TNPFITTER::DrawFit( fit, sigma, window );

  double down = fit->GetBackgroundDownFunction()->GetParameter(0);
  double up = fit->GetBackgroundUpFunction()->GetParameter(0);

  std::cout << "Printing a variable from Up fit: " << up << std::endl;
  std::cout << "Printing a variable from Down fit: " << down << std::endl;

  return testStatus;
}
