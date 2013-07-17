#include "GrapherTools/ScaleFactor.h"
#include "TFile.h"
#include "TH1F.h"
#include <iostream>

int main()
{
  TFile* file = new TFile("./testhist.root","OPEN");
  if(file == NULL)
  {
    std::cerr << "File not found" << std::endl;
    return(0);
  };

  TH1F* histoOne = dynamic_cast<TH1F*>(file->Get("h_tag_z0_PV"));
  TH1F* histoTwo = dynamic_cast<TH1F*>(file->Get("h_tag_z0_PV_wgt"));

  GT::ScaleFactor* testSF = new GT::ScaleFactor("testOutput", histoOne, histoTwo);
  testSF->SetXaxisTitle("pT [GeV]");
  testSF->SetYaxisTitle("Entries");
  testSF->SetSFaxisTitle("SF Title");
  testSF->doLog = 1;
  testSF->colorTwo = 4; testSF->markerStyleTwo = 25; testSF->histo1Title = "First";
  testSF->colorOne = 44; testSF->markerStyleOne = 26; testSF->histo2Title = "Second";
  testSF->Draw();
  testSF->SaveAs("./test.png", "png");
}
