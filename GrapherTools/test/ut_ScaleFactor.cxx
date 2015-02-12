#include "GrapherTools/ScaleFactor.h"
#include "TFile.h"
#include "TH1F.h"
#include <iostream>
#include <memory>

int main() {
  TFile file { "./testhist.root", "OPEN" };

  std::unique_ptr<TObject> firstObject(file.Get("h_tag_z0_PV"));
  if(firstObject) {
     std::cerr << "Couldn't find histogram h_tag_z0_PV\n";
  }
  
  std::unique_ptr<TObject> secondObject(file.Get("h_tag_z0_PV_wgt"));
  if(secondObject) {
    std::cerr << "Couldn't find histogram h_tag_z0_PV_wgt\n";
  }

  std::unique_ptr<TH1F> firstHistogram(static_cast<TH1F*>(firstObject.release()));
  std::unique_ptr<TH1F> secondHistogram(static_cast<TH1F*>(secondObject.release()));

  GT::ScaleFactor testSF { "testOutput", std::move(firstHistogram), std::move(secondHistogram) };
  testSF.SetXaxisTitle("pT [GeV]");
  testSF.SetYaxisTitle("Entries");
  testSF.SetSFaxisTitle("SF Title");
  testSF.colorTwo = 4;
  testSF.markerStyleTwo = 25;
  testSF.histo1Title = "First";
  testSF.colorOne = 44;
  testSF.markerStyleOne = 26;
  testSF.histo2Title = "Second";
  testSF.Draw();
  testSF.SaveAs("./test.png", "png");
}
