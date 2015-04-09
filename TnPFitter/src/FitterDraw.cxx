#include "TnPFitter/FitterDraw.h"

#include <iostream>

#include "TFile.h"
#include "TLine.h"
#include <TF1.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TPaveText.h>

FitterDraw::FitterDraw(IFitter* fitter, int sigma, int window)
  : fFitter(fitter),
    fSigma{sigma},
    fWindow{window} {
  configFile = new TFile{"$ROOTCOREDIR/data/TnPFitter/TnPFitter-FittingConfig.xml", "OPEN"};

  if(configFile->IsZombie()) {
    throw(std::runtime_error("Failed to load configuration XML file"));
  }

  configFile->GetObject("BkgUpConfig", bkgUp);
  configFile->GetObject("BkgDownConfig", bkgDown);
  configFile->GetObject("BkgConfig", bkg);
  configFile->GetObject("SignalConfig", signal);
  configFile->GetObject("NominalConfig", nominal);

  configFile->Close();
  delete configFile;

  if(fFitter == nullptr) {
    throw(std::runtime_error("Fitter object is not configured correctly"));
  }

  auto histogram = fFitter->GetHistogram();

  histMin = histogram->GetMinimum() - histogram->GetMaximum() * 0.05;
  histMax = histogram->GetMaximum() * 1.2;
}

FitterDraw::~FitterDraw() {
  configFile->Close();

  delete bkgUp;
  delete bkgDown;
  delete bkg;
  delete signal;
  delete nominal;
  delete configFile;
}

void FitterDraw::SetupLines(const std::string& options) {
  (void) options;
  SetupLine(fFitter->GetSignalFunction(), signal);
  SetupLine(fFitter->GetBackgroundFunction(), bkg);
  SetupLine(fFitter->GetCompositeFunction(), nominal);
  SetupLine(fFitter->GetBackgroundUpFunction(), bkgUp);
  SetupLine(fFitter->GetBackgroundDownFunction(), bkgDown);
  SetupLine(fFitter->GetCompositeDownFunction(), bkgDown);
  SetupLine(fFitter->GetCompositeUpFunction(), bkgUp);

  auto narrowSigmaLow = fFitter->GetSigmaLow(fSigma);
  auto narrowSigmaHigh = fFitter->GetSigmaHigh(fSigma);
  auto wideSigmaLow = fFitter->GetSigmaLow(fSigma + fWindow);
  auto wideSigmaHigh = fFitter->GetSigmaHigh(fSigma + fWindow);

  fiveLow = new TLine{wideSigmaLow, histMin, wideSigmaLow, histMax};
  fiveHigh = new TLine{wideSigmaHigh, histMin, wideSigmaHigh, histMax};
  threeLow = new TLine{narrowSigmaLow, histMin, narrowSigmaLow, histMax};
  threeHigh = new TLine{narrowSigmaHigh, histMin, narrowSigmaHigh, histMax};

  fiveLow->SetLineColor(3);
  fiveLow->SetLineWidth(2);
  fiveHigh->SetLineColor(3);
  fiveHigh->SetLineWidth(2);

  threeLow->SetLineColor(6);
  threeLow->SetLineWidth(2);
  threeHigh->SetLineColor(6);
  threeHigh->SetLineWidth(2);
}

void FitterDraw::SetupBox() {
  box = new TPaveText{0.2, 0.48, 0.45, 0.9, "NDC"};
  for(auto parIdx = 0; parIdx != fFitter->GetCompositeFunction()->GetNpar(); parIdx++) {
    auto name = fFitter->GetCompositeFunction()->GetParName(parIdx);
    auto val = fFitter->GetCompositeFunction()->GetParameter(parIdx);
    auto err = fFitter->GetCompositeFunction()->GetParError(parIdx);
    std::stringstream str(name);
    str << " : " << val << "+-" << err;

    box->AddText(str.str().c_str());
  }
}

void FitterDraw::Draw(const std::string& options) {
  SetupLines(options);
  SetupBox();

  auto name = fFitter->GetName();
  auto c1 = new TCanvas(name.c_str(), name.c_str(), 0, 0, 800, 600);
  auto histogram = fFitter->GetHistogram();
  histogram->GetYaxis()->SetRangeUser(histMin, histMax);

  c1->Draw();
  histogram->Draw();

  fFitter->GetCompositeFunction()->Draw("SAME");
  fFitter->GetBackgroundFunction()->Draw("SAME");
  fFitter->GetSignalFunction()->Draw("SAME");
  fFitter->GetBackgroundDownFunction()->Draw("SAME");
  fFitter->GetBackgroundUpFunction()->Draw("SAME");
  fFitter->GetCompositeDownFunction()->Draw("SAME");
  fFitter->GetCompositeUpFunction()->Draw("SAME");

  fiveLow->Draw();
  fiveHigh->Draw();
  threeLow->Draw();
  threeHigh->Draw();
  box->Draw();

  auto filename = fFitter->GetFunctionName() + "-" + name + ".pdf";

  c1->SaveAs(filename.c_str(), "pdf");
  c1->Close();
}

void FitterDraw::SetupLine(TF1* line, LineAttrib* attribute) {
  if(line == nullptr) {
    std::cerr << "This line is not properly setup\n";
    return;
  }

  line->SetLineColor(attribute->color);
  line->SetLineWidth(attribute->width);
  line->SetLineStyle(attribute->style);

  line->SetNpx(1000);
}

#ifdef __CINT__
ClassImp(FitterDraw)
#endif
