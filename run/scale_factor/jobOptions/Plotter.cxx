#include "TFile.h"
#include "TH1F.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TLegend.h"
#include <iostream>

void Plotter(const std::string& path, const std::string& outputPath)
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
  
  float colors[] = { 4, 2 };
  std::string labels[] = { "T&P data Period B", 
                           "T&P Pythia Direct J/#Psi #rightarrow #mu#mu" };

  float markerStyle = 21;

  std::string effTitle[] = { "Match #chi^{2} Tagger Efficiency",
                             "Reconstruction Efficiency" };

  TFile* file = new TFile(path.c_str());

  for(size_t regionIdx = 0; regionIdx != 10; regionIdx++)
  {
    for(size_t effIdx = 0; effIdx != 2; effIdx++)
    {
      std::string regionName = regions[regionIdx];
      std::string effName = eff[effIdx];

      std::cout << "Processing " << regionName << " region" << std::endl;
      std::cout << "Processing " << effName << " efficiency" << std::endl;

      std::string stackName = Form("h_pt_%s_%s_stack", regionName.c_str(), effName.c_str());
      std::string sfName = Form("h_pt_%s_%s_SF", regionName.c_str(), effName.c_str());

      std::cout << "Stack Name " << stackName << std::endl;
      std::cout << "SF Name " << sfName << std::endl;

      THStack* stack = dynamic_cast<THStack*> (file->Get(stackName.c_str()));
      TH1F* SF = dynamic_cast<TH1F*> (file->Get(sfName.c_str()));

      if(!stack)
      {
        std::cout << "Stack not loaded" << std::endl;
        delete file;
        exit;
      };

      TIter next(stack->GetHists());

      TH1F* h1; size_t i = 0;
      leg = new TLegend(0.2,0.05,0.7,0.2);  //coordinates are fractions
      leg->SetFillColor(0);
      leg->SetShadowColor(0);
      leg->SetLineColor(1);
      
      while( (h1 = dynamic_cast<TH1F*>(next())) )
      {
        h1->SetMarkerColor(colors[i]);
        h1->SetLineColor(colors[i]);
        h1->SetMarkerStyle(markerStyle);
        h1->SetFillColor(0);
        leg->AddEntry(h1, labels[i].c_str());
        i++;
      };

      TCanvas* canvas = new TCanvas( Form("c_%s_%s", regionName.c_str(), effName.c_str()),
                                    effTitle[effIdx].c_str(), 900, 700 );

      TPad top_leftpad("top_leftpad", "top_leftpad",0,0.4, 1.0, 1.0);
      top_leftpad.Draw();
      top_leftpad.cd();
      top_leftpad.SetBottomMargin(0);
      
      stack->Draw("nostack");
      // stack->GetXaxis()->SetLimits(4000,12000);
      stack->GetYaxis()->SetNdivisions(505);
      stack->GetYaxis()->SetTitle( effTitle[effIdx].c_str() );
      stack->SetMaximum(1.2);
      stack->SetMinimum(0.5);

      if(TString(regionName).Contains("Crack"))
      {
        stack->SetMaximum(1.2);
        stack->SetMinimum(0.0);
      };
      
      leg->Draw();

      canvas->cd();

      TPad bottom_leftpad("bottom_leftpad", "bottom_leftpad", 0, 0.03, 1.0, 0.4);
      bottom_leftpad.Draw();
      bottom_leftpad.cd();
      bottom_leftpad.SetTopMargin(0);
      bottom_leftpad.SetGrid(1,1);
      
      SF->SetTitle("Data/MC Scale Factor");
      SF->SetMarkerColor(4);
      SF->SetLineColor(4);
      SF->SetMarkerStyle(21);
      SF->SetFillColor(0);
      SF->Draw("P");
      SF->GetXaxis()->SetTitle("#mu P_{T} [GeV]");
      SF->GetXaxis()->SetLabelSize(0.08);
      SF->GetXaxis()->SetTitleSize(0.08);
      SF->GetXaxis()->SetTitleOffset(0.92);
      
      SF->GetYaxis()->SetRangeUser(0.6, 1.4);
      SF->GetYaxis()->SetTitle("Data/MC Scale Factor");
      SF->GetYaxis()->SetNdivisions(505);
      SF->GetYaxis()->SetTitleSize(0.08);
      SF->GetYaxis()->SetTitleOffset(0.7);

      std::cout << "Outputting to: " << outputPath.c_str() << std::endl;
      
      gSystem->mkdir(outputPath.c_str());
      canvas->SaveAs(Form("%s/%s_%s.png", outputPath.c_str(), regionName.c_str(), effName.c_str()), "png");
    };
  };
};
