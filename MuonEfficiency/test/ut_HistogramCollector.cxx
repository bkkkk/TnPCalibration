#include "MuonEfficiency/HistogramCollector.h"
#include "PATCore/TAccept.h"
#include "TCanvas.h"
#include <iostream>

int main() 
{
  HC::HistogramCollector* histoCollector = new HC::HistogramCollector("stuff", NULL);
  histoCollector->CreateHistogram("Test1D", "Test Title 1D", 10, 0, 10);
  histoCollector->CreateHistogram("Test2D", "Test Title 2D", 10, 0, 10, 10, 0, 10);
  histoCollector->CreateHistogram("Test3D", "Test Title 3D", 10, 0, 10, 10, 0, 10, 10, 0, 10);

  // Getting 1D histogram
  TH1F* hist = histoCollector->GetHistogram1D("Test1D");
  if(hist!=NULL)
  {
    std::cout << "All is well" << std::endl;
  };

  TH1F* histNull = histoCollector->GetHistogram1D("NotPresent");
  if(histNull == NULL)
  {
    std::cout << "Test search for not present histogram: Pass" << std::endl;
  } else
  {
    std::cout << "Test search for not present histogram: Fail" << std::endl;
  };

  std::cout << "Creating TAccept object" << std::endl;
  Root::TAccept* accept = new Root::TAccept();
  accept->addCut("TestNameCut1", "Cut 1"); accept->addCut("TestNameCut2", "Cut 2");
  accept->addCut("TestNameCut3", "Cut 3"); accept->addCut("TestNameCut4", "Cut 4");

  histoCollector->CreateHistogram("TestCutflow", "Test Cut Flow Title", accept);

  accept->clear();
  accept->setCutResult("TestNameCut1", true);
  accept->setCutResult("TestNameCut2", true);
  accept->setCutResult("TestNameCut3", false);
  accept->setCutResult("TestNameCut4", true);

  histoCollector->FillHistogram("TestCutflow", accept, 1);

  accept->clear();
  accept->setCutResult("TestNameCut1", false);
  accept->setCutResult("TestNameCut2", true);
  accept->setCutResult("TestNameCut3", true);
  accept->setCutResult("TestNameCut4", true);

  histoCollector->FillHistogram("TestCutflow", accept, 1);

  TH1F* cutflow = histoCollector->GetHistogram1D("TestCutflow");
  
  TCanvas c1;
  if(cutflow!=NULL) cutflow->Draw();
  c1.SaveAs("TestOutput.eps","eps");
};