#include "ut_HistogramCollector"
#include "MuonEfficiency/HistogramCollector.h"
#include "PATCore/TAccept.h"
#include "TCanvas.h"
#include <iostream>

int main() {
  // Setup
  HC::HistogramCollector* histoCollector =
      new HC::HistogramCollector("stuff", NULL);
  histoCollector->CreateHistogram("Test1D", "Test Title 1D", 10, 0, 10);
  histoCollector->CreateHistogram(
      "Test2D", "Test Title 2D", 10, 0, 10, 10, 0, 10);
  histoCollector->CreateHistogram(
      "Test3D", "Test Title 3D", 10, 0, 10, 10, 0, 10, 10, 0, 10);

  // Test returns a histogram when histogram is present
  TH1F* hist = histoCollector->GetHistogram1D("Test1D");
  if (hist != NULL) {
    std::cout << "All is well" << std::endl;
  };

  // Test returns a null pointer if histogram not found
  TH1F* histNull = histoCollector->GetHistogram1D("NotPresent");
  if (histNull == NULL) {
    std::cout << "Test search for not present histogram: Pass" << std::endl;
  } else {
    std::cout << "Test search for not present histogram: Fail" << std::endl;
  };

  // Test creating cutflow histograms
  // Create a fake set of cuts
  std::cout << "Creating TAccept object" << std::endl;
  Root::TAccept* accept = new Root::TAccept();
  accept->addCut("TestNameCut1", "Cut 1");
  accept->addCut("TestNameCut2", "Cut 2");
  accept->addCut("TestNameCut3", "Cut 3");
  accept->addCut("TestNameCut4", "Cut 4");
  histoCollector->CreateHistogram("TestCutflow", "Test Cut Flow Title", accept);

  // Fill one event
  accept->clear();
  accept->setCutResult("TestNameCut1", true);
  accept->setCutResult("TestNameCut2", true);
  accept->setCutResult("TestNameCut3", false);
  accept->setCutResult("TestNameCut4", true);
  histoCollector->FillHistogram("TestCutflow", accept, 1);

  // Fill another event
  accept->clear();
  accept->setCutResult("TestNameCut1", false);
  accept->setCutResult("TestNameCut2", true);
  accept->setCutResult("TestNameCut3", true);
  accept->setCutResult("TestNameCut4", true);
  histoCollector->FillHistogram("TestCutflow", accept, 1);

  // Output cutflow for visual check
  TH1F* cutflow = histoCollector->GetHistogram1D("TestCutflow");
  TCanvas c1;
  if (cutflow != NULL)
    cutflow->Draw();
  c1.SaveAs("TestOutput.eps", "eps");
}