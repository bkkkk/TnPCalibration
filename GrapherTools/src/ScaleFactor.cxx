// These are the default plotting settings
// numerator.markerStyle = 21;
// numerator.markerColor = kBlue;
// denominator.markerStyle = 21;
// denominator.markerColor = kRed;
// attributes.titleSize = 0.08;
// attributes.titleOffset = 0.92;
// attributes.markerStyle = 21;
// attributes.markerColor = 4;
// attributes.minimum = 0.6;
// attributes.maximum = 1.;

#include "GrapherTools/ScaleFactor.h"

#include "TH1.h"
#include "TPad.h"
#include "TLegend.h"

#include <iostream>

GT::ScaleFactor::ScaleFactor(SFAttributes sfAttributes,
                             SFComponent sfNumerator,
                             SFComponent sfDenominator)
    : attributes{sfAttributes},
      numerator{sfNumerator},
      denominator{sfDenominator},
      canvas{attributes.getTitle().c_str(),
             attributes.getTitle().c_str(),
             900,
             700},
      stack{attributes.getTitle().c_str(), attributes.getTitle().c_str()},
      leg{0.6, 0.7, 0.8, 0.8},
      SF{"DivideTemp",
         "",
         numerator.getHistogram()->GetNbinsX(),
         attributes.getMaximum(),
         attributes.getMinimum()} {
  SF.Divide(numerator.getHistogram(), denominator.getHistogram());

  leg.SetFillColor(0);
  leg.SetShadowColor(0);
  leg.SetLineColor(0);
}

void GT::ScaleFactor::Draw() {
  canvas.cd();
  enableMiddleTicks(canvas);
  canvas.Draw();

  auto doLog = false;
  TPad padTopLeft{"topPad", "Top", 0, 0.4, 1.0, 1.0};
  padTopLeft.SetBottomMargin(0);
  padTopLeft.SetLogy(doLog);
  padTopLeft.Draw();

  addComponentToStack(numerator);
  addComponentToStack(denominator);
  drawStack();
  leg.Draw();

  canvas.cd();
  TPad padBottomRight{"bottomPad", "Bottom", 0, 0.03, 1.0, 0.4};
  padBottomRight.Draw();
  padBottomRight.cd();
  padBottomRight.SetTopMargin(0);
  padBottomRight.SetGrid(1, 1);
  setupScaleFactorHistogram();
}

void GT::ScaleFactor::setupScaleFactorHistogram() {
  SF.SetMarkerColor(attributes.getMarkerColor());
  SF.SetLineColor(attributes.getMarkerColor());
  SF.SetMarkerStyle(attributes.getMarkerStyle());
  SF.SetFillColor(0);
  SF.SetStats(false);
  SF.Draw("P");
  SF.GetXaxis()->SetTitle(attributes.getXAxisTitle().c_str());
  SF.GetXaxis()->SetLabelSize(13);
  SF.GetXaxis()->SetTitleSize(attributes.getTitleSize());
  SF.GetXaxis()->SetTitleOffset(attributes.getTitleOffset());

  SF.GetYaxis()->SetTitle(attributes.getYAxisTitle().c_str());
  SF.GetYaxis()->CenterTitle(true);
  SF.GetYaxis()->SetNdivisions(505);
  SF.GetYaxis()->SetTitleSize(0.08);
  SF.GetYaxis()->SetTitleOffset(0.7);
}

void GT::ScaleFactor::enableMiddleTicks(TCanvas& inCanvas) {
  inCanvas.SetTickx(1);
  inCanvas.SetTicky(1);
}

void GT::ScaleFactor::addComponentToStack(SFComponent component) {
  stack.Add(component.getHistogram());
  leg.AddEntry(component.getHistogram(), component.getTitle().c_str());
}

void GT::ScaleFactor::drawStack() {
  stack.Draw("nostack");
  stack.GetYaxis()->SetNdivisions(505);
  stack.GetYaxis()->SetTitle(attributes.getYAxisTitle().c_str());
}

void GT::ScaleFactor::SaveAs(std::string path, std::string format) {
  canvas.SaveAs(path.c_str(), format.c_str());
}

#ifdef __CINT__
ClassImp(GT::ScaleFactor)
#endif
