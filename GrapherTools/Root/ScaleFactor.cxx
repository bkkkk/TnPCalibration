#include "GrapherTools/ScaleFactor.h"
#include <iostream>

//______________________________________________________________________________
GT::ScaleFactor::ScaleFactor(const SFAttributes& attributes, const SFComponent& numerator, const SFComponent& denominator)
 : histo1(std::move(h1)),
   histo2(std::move(h2)),
   canvas(name.c_str(), name.c_str(), 900, 700),
   padTopLeft("top_leftpad", "top_leftpad", 0, 0.4, 1.0, 1.0),
   padBottomRight("bottom_leftpad", "bottom_leftpad", 0, 0.03, 1.0, 0.4),
   stack("", ""),
   markerStyleOne(21),
   colorOne(kBlue),
   markerStyleTwo(21),
   colorTwo(kRed),
   sfTitleSize(0.08),
   sfTitleOffset(0.92),
   sfMarkerStyle(21),
   sfMarkerColor(4),
   sfRangeMin(0.6),
   sfRangeMax(1.4)
{
  std::cout << "Making pads, SF and Stack" << std::endl;
  
  SF = new TH1F("DivideTemp", "", h1->GetNbinsX(), h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax());
  SF->Divide(histo1.get(), histo2.get());

  std::cout << "All done" << std::endl;
};

GT::ScaleFactor::~ScaleFactor() {
  delete SF;
};

void GT::ScaleFactor::SetXaxisTitle(const std::string& title) {
  xAxisTitle = title;
}

void GT::ScaleFactor::SetYaxisTitle(const std::string& title) {
  yAxisTitle = title;
}

void GT::ScaleFactor::SetSFaxisTitle(const std::string& title) {
  sfTitle = title;
}

void GT::ScaleFactor::SetSFRange(const float min, const float max) {
  sfRangeMax = max;
  sfRangeMin = min;
}

void GT::ScaleFactor::Draw() {
  histo1->SetMarkerColor(colorOne);
  histo1->SetLineColor(colorOne);
  histo1->SetMarkerStyle(markerStyleOne);
  
  histo2->SetMarkerColor(colorTwo);
  histo2->SetLineColor(colorTwo);
  histo2->SetMarkerStyle(markerStyleTwo);

  TLegend leg { 0.6,0.7,0.8,0.8 };
  leg.SetFillColor(0);
  leg.SetShadowColor(0);
  leg.SetLineColor(0);

  stack.Add(histo1.get());
  leg.AddEntry(histo1.get(), histo1Title.c_str());
  
  stack.Add(histo2.get());
  leg.AddEntry(histo2.get(), histo2Title.c_str());

  // Draw Canvas
  canvas.cd();
  canvas.SetTickx(1);
  canvas.SetTicky(1);
  canvas.Draw();

  // Draw Top Pad
  padTopLeft.Draw();
  padTopLeft.cd();
  padTopLeft.SetBottomMargin(0);
  padTopLeft.SetLogy(doLog);

  // Draw Stack
  stack.Draw("nostack");
  stack.GetYaxis()->SetNdivisions(505);
  stack.GetYaxis()->SetTitle( yAxisTitle.c_str() );

  leg.Draw();

  // Draw Bottom Pad
  canvas.cd();
  padBottomRight.Draw();
  padBottomRight.cd();
  padBottomRight.SetTopMargin(0);
  padBottomRight.SetGrid(1,1);
  
  SF->SetMarkerColor(sfMarkerColor); SF->SetLineColor(sfMarkerColor);
  SF->SetMarkerStyle(sfMarkerStyle);
  SF->SetFillColor(0);
  SF->SetStats(false);
  SF->Draw("P");
  SF->GetXaxis()->SetTitle(xAxisTitle.c_str());
  SF->GetXaxis()->SetLabelSize(sfTitleSize);
  SF->GetXaxis()->SetTitleSize(sfTitleSize);
  SF->GetXaxis()->SetTitleOffset(sfTitleOffset);
  
  SF->GetYaxis()->SetTitle(sfTitle.c_str());
  SF->GetYaxis()->CenterTitle(true);
  SF->GetYaxis()->SetNdivisions(505);
  SF->GetYaxis()->SetTitleSize(0.08);
  SF->GetYaxis()->SetTitleOffset(0.7);
};

void GT::ScaleFactor::SaveAs(const std::string& path, const std::string& format) {
  canvas.SaveAs(path.c_str(), format.c_str());
};

#ifdef _MAKE_CINT_
ClassImp(GT::ScaleFactor)
#endif
