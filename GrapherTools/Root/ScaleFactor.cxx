#include "GrapherTools/ScaleFactor.h"
#include <iostream>

//______________________________________________________________________________
GT::ScaleFactor::
ScaleFactor( const std::string& name, TH1* h1, TH1* h2)
 : histo1(h1),
   histo2(h2),
   canvas(new TCanvas(name.c_str(), name.c_str(), 900, 700) ),
   padTopLeft(NULL),
   padBottomRight(NULL),
   stack(new THStack("", "")),
   markerStyleOne(21),
   markerStyleTwo(21),
   colorOne(kBlue),
   colorTwo(kRed),
   doLog(0),
   sfTitleSize(0.08),
   sfTitleOffset(0.92),
   sfMarkerStyle(21),
   sfMarkerColor(4),
   sfRangeMin(0.6),
   sfRangeMax(1.4)
{
  std::cout << "Making pads, SF and Stack" << std::endl;
  padTopLeft = new TPad("top_leftpad", "top_leftpad", 0, 0.4, 1.0, 1.0);
  padBottomRight = new TPad("bottom_leftpad", "bottom_leftpad", 0, 0.03, 1.0, 0.4);
  
  SF = new TH1F("DivideTemp", "", h1->GetNbinsX(), h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax());
  SF->Divide(histo1, histo2);

  std::cout << "All done" << std::endl;
};

//______________________________________________________________________________
GT::ScaleFactor::
~ScaleFactor()
{
  delete histo1;
  delete histo2;
  delete SF;
  delete padTopLeft;
  delete padBottomRight;
  delete stack;
  delete canvas;
};

//______________________________________________________________________________
void GT::ScaleFactor::
SetXaxisTitle(const std::string& title)
{
  xAxisTitle = title;
};

//______________________________________________________________________________
void GT::ScaleFactor::
SetYaxisTitle(const std::string& title)
{
  yAxisTitle = title;
};

//______________________________________________________________________________
void GT::ScaleFactor::
SetSFaxisTitle(const std::string& title)
{
  sfTitle = title;
};

//______________________________________________________________________________
void GT::ScaleFactor::
SetSFRange(const float min, const float max)
{
  sfRangeMax = max;
  sfRangeMin = min;
};

//______________________________________________________________________________
void GT::ScaleFactor::
Draw()
{
  std::cout << "Drawing" << std::endl;
 
  histo1->SetMarkerColor(colorOne); histo1->SetLineColor(colorOne); histo1->SetMarkerStyle(markerStyleOne);
  histo2->SetMarkerColor(colorTwo); histo2->SetLineColor(colorTwo); histo2->SetMarkerStyle(markerStyleTwo);

  TLegend* leg = new TLegend(0.6,0.7,0.8,0.8);
  leg->SetFillColor(0);
  leg->SetShadowColor(0);
  leg->SetLineColor(0);

  stack->Add(histo1); leg->AddEntry(histo1, histo1Title.c_str());
  stack->Add(histo2); leg->AddEntry(histo2, histo2Title.c_str());

  // Draw Canvas
  canvas->cd();
  canvas->SetTickx(1);
  canvas->SetTicky(1);
  canvas->Draw();

  // Draw Top Pad
  padTopLeft->Draw();
  padTopLeft->cd();
  padTopLeft->SetBottomMargin(0);
  padTopLeft->SetLogy(doLog);

  // Draw Stack
  stack->Draw("nostack");
  stack->GetYaxis()->SetNdivisions(505);
  stack->GetYaxis()->SetTitle( yAxisTitle.c_str() );

  leg->Draw();

  // Draw Bottom Pad
  canvas->cd();
  padBottomRight->Draw();
  padBottomRight->cd();
  padBottomRight->SetTopMargin(0);
  padBottomRight->SetGrid(1,1);
  
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
  std::cout << "Done" << std::endl;
};

//______________________________________________________________________________
void GT::ScaleFactor::
SaveAs(const std::string& path, const std::string& format)
{
  if(canvas != NULL) canvas->SaveAs(path.c_str(), format.c_str());
  else std::cerr << "This canvas is has not been initialized" << std::endl;
  return;
};

ClassImp(GT::ScaleFactor)

