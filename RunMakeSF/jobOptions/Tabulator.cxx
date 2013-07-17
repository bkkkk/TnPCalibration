#include "TFile.h"
#include "TH1F.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TLegend.h"
#include <iostream>
#include <sstream>


void Tabulator(const std::string& path)
{

  std::string regions[] = { "Forward C",
                            "Endcap C",
                            "Transition C",
                            "Barrel C",
                            "Crack C",
                            "Crack A",
                            "Barrel A", 
                            "Transition A",
                            "Endcap A",
                            "Forward A" };

  std::string eff[] = {"smt", "reco"};

  TFile* file = new TFile(path.c_str());
  
  TH1F* sampleHisto = dynamic_cast<TH1F*> (file->Get("h_pt_Crack A_reco_SF"));

  std::cout.width(6);
  std::cout << "\t" << "Region";
  for(int ptBinIdx = 1; ptBinIdx != sampleHisto->GetNbinsX(); ptBinIdx++)
  {
    double lowEdge = sampleHisto->GetBinLowEdge(ptBinIdx) / 1000;
    double highEdge = (sampleHisto->GetBinLowEdge(ptBinIdx) + sampleHisto->GetBinWidth(ptBinIdx)) / 1000;

    std::cout << "\t"<< lowEdge << "-" << highEdge;
  }; 
  std::cout << std::endl;

  std::cout.precision(4);

  for(size_t effIdx = 0; effIdx != 2; effIdx++)
  {
    std::string effName = eff[effIdx];
    std::cout << "Processing " << effName << " efficiency" << std::endl;

    for(size_t regionIdx = 0; regionIdx != 10; regionIdx++)
    {
      std::string regionName = regions[regionIdx];
      std::string sfName = Form("h_pt_%s_%s_SF", regionName.c_str(), effName.c_str());

      TH1F* SF = dynamic_cast<TH1F*> (file->Get(sfName.c_str()));

      if(SF==NULL) { std::cout << "SF is empty"; };
      std::cout.width(14);
      std::cout << regionName;      

      for(int ptBin = 1; ptBin != SF->GetNbinsX(); ptBin++)
      {
        std::cout << "\t" << SF->GetBinContent(ptBin) << "+-" << SF->GetBinError(ptBin);
      };
      std::cout << std::endl;
    };
  };
};
