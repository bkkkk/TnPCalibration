#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TKey.h"
#include "TList.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TObject.h"
#include "TLegend.h"
#include <iostream>
#include <sstream>
#include "TSystem.h"

void AllPlotter( const std::string& dataPath,
                 const std::string& mcPath,
                 const std::string& outputDir="./latest")
{
  gSystem->mkdir(Form("%s", outputDir.c_str()));

  TFile* dataFile = new TFile(dataPath.c_str());
  TFile* mcFile = new TFile(mcPath.c_str());

  TList* dataKeys = dataFile->GetListOfKeys();
  TList* mcKeys = mcFile->GetListOfKeys();

  if(dataKeys->GetSize() != mcKeys->GetSize()) {
    dataKeys->Print();
    mcKeys->Print();
    std::cout << "ERROR :: These samples don't have compatible histograms" << std::endl;
    return;
  }

  unsigned int numberOfHistos = dataKeys->GetSize();
  std::cout << "INFO :: There are " << numberOfHistos << " in the files" << std::endl;

  float markerStyle = 21;
  float colors[] = { 4, 2 };
  std::string labels[] = { "T&P Data Period", 
                           "T&P Direct J/#Psi #rightarrow #mu#mu" };

  TLegend* leg;

  TIter next(dataKeys);
  next();

  // @TODO - This is for super hack, remove it please
  unsigned int varIdx = 0;

  while( TObject* obj = next() )
  {
    std::string varName = obj->GetName();
    std::cout << "Processing " << varName << " variable" << std::endl;

    TH1* h_mc = dynamic_cast<TH1*> (mcFile->Get(varName.c_str()));
    TH1* h_data = dynamic_cast<TH1*> (dataFile->Get(varName.c_str()));
    
    std::string xTitle = h_mc->GetXaxis()->GetTitle();
    std::string yTitle = h_mc->GetYaxis()->GetTitle();
    std::string title = h_mc->GetTitle();

    float dataIntegral = h_data->Integral(0, 100000);
    float mcIntegral = h_mc->Integral(0,100000);
    h_mc->Scale(dataIntegral/mcIntegral);

    stringstream str;y
    str << title << ";" << xTitle << ";" << yTitle;
    std::string newTitle = str.str();

    int is2D = 0;
    if (dynamic_cast<TH2F*> (h_mc) != NULL) {
      std::cout << "Working with 2D" << std::endl;
      is2D = 1;
    }

    THStack* stack = new THStack("", newTitle.c_str());
    stack->Add(h_data);
    stack->Add(h_mc);

    TIter nextStack(stack->GetHists());

    TH1* h1; size_t i = 0;
    if(varIdx == 30)
    {
      leg = new TLegend(0.3, 0.6, 0.05, 0.15);
    }
    else
    {
      leg = new TLegend(0.6,0.8,0.9,0.9);  //coordinates are fractions  
    }
    leg->SetFillColor(0);
    leg->SetShadowColor(0);
    leg->SetLineColor(0);
    
    while( (h1 = dynamic_cast<TH1*>(nextStack())) )
    {
      h1->SetMarkerColor(colors[i]);
      h1->SetLineColor(colors[i]);
      
      if(is2D != 1) {
        h1->SetMarkerStyle(markerStyle);
        h1->SetFillColor(0);
      }

      std::string label = labels[i];

      if(i == 0)
      {
        if(TString(dataPath).Contains("periodB")) label.append("B");
        if(TString(dataPath).Contains("periodA")) label.append("A");
      }
    
      leg->AddEntry(h1, label.c_str());
      i++;
    }

    TCanvas* canvas = new TCanvas(varName.c_str(), varName.c_str(), 900, 700 );
    
    std::string opt = "nostack";
    if(is2D == 1) { opt += "box"; }

    stack->Draw(opt.c_str());
    stack->GetYaxis()->SetNdivisions(505);
    leg->Draw();

    canvas->cd();

    if(TString(varName.c_str()).Contains("z0") && is2D != 1) canvas->SetLogy();

    canvas->SaveAs(Form("%s/%s.pdf", outputDir.c_str(), varName.c_str()), "pdf");
    canvas->SaveAs(Form("%s/%s.png", outputDir.c_str(), varName.c_str()), "png");
  };
};
