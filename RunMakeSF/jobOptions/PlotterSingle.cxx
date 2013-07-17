#include "TFile.h"
#include "TH1F.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TLegend.h"
#include <iostream>

void PlotterSingle(const std::string& path, const std::string& outPath)
{

  std::string eff[] = {"smt", "reco"};
  
  float colors[] = { 4, 2 };
  std::string labels[] = { "T&P data", 
                           "T&P Pythia Direct J/#Psi #rightarrow #mu#mu" };

  float markerStyle = 21;

  std::string effTitle[] = { "Match #chi^{2} Tagger Efficiency",
                             "Reconstruction Efficiency" };

  TFile* file = new TFile(path.c_str());
  gSystem->mkdir(outPath.c_str());


  std::string variables[] = { "etcone20", "etcone30", "etcone40",
                              "ptcone20", "ptcone30", "ptcone40",
                              "nucone20", "nucone30", "nucone40",
                              "pt", "eta", "phi" };

  std::string xtitle[] = { "Probe etcone20 [GeV]", "Probe etcone30 [GeV]", "Probe etcone40 [GeV]",
                           "Probe ptcone20 [GeV]", "Probe ptcone30 [GeV]", "Probe ptcone40 [GeV]",
                           "Probe nucone20", "Probe nucone30", "Probe nucone40",
                           "Probe p_{T} [MeV]", "Probe #eta", "Probe #phi" };
  
  for (int varIdx = 0; varIdx != 12; varIdx++)
  {
    std::string var = variables[varIdx];

    for(size_t effIdx = 0; effIdx != 2; effIdx++)
    {
      std::string effName = eff[effIdx];

      std::cout << "Processing " << effName << " efficiency" << std::endl;

      std::string stackName = Form("h_%s_%s_stack", var.c_str(), effName.c_str());
      std::string sfName = Form("h_%s_%s_SF", var.c_str(), effName.c_str());

      std::cout << "Stack Name " << stackName << std::endl;
      std::cout << "SF Name " << sfName << std::endl;

      THStack* stack = dynamic_cast<THStack*> (file->Get(stackName.c_str()));
      TH1F* SF = dynamic_cast<TH1F*> (file->Get(sfName.c_str()));

      if(!stack)
      {
        std::cout << "Stack not loaded" << std::endl;
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

      TCanvas* canvas = new TCanvas( Form("c_%s_%s", var.c_str(), effName.c_str()),
                                    effTitle[effIdx].c_str(), 900, 700 );

      TPad top_leftpad("top_leftpad", "top_leftpad",0,0.4, 1.0, 1.0);
      top_leftpad.Draw();
      top_leftpad.cd();
      top_leftpad.SetBottomMargin(0);
      
      stack->Draw("nostack");
      // stack->GetXaxis()->SetLimits(4000,20000);
      stack->GetYaxis()->SetNdivisions(505);
      stack->GetXaxis()->SetTitle( var.c_str() );
      stack->GetYaxis()->SetTitle( effTitle[effIdx].c_str() );
      stack->SetMaximum(1.2);
      stack->SetMinimum(0.5);
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
      SF->GetXaxis()->SetTitle(xtitle[varIdx].c_str());
      SF->GetXaxis()->SetLabelSize(0.08);
      SF->GetXaxis()->SetTitleSize(0.08);
      SF->GetXaxis()->SetTitleOffset(0.92);
      // SF->GetXaxis()->SetRangeUser(4000, 20000);
      
      SF->GetYaxis()->SetRangeUser(0.6, 1.4);
      SF->GetYaxis()->SetTitle("Data/MC Scale Factor");
      SF->GetYaxis()->SetTitleSize(0.08);
      SF->GetYaxis()->SetTitleOffset(0.7);
      SF->GetYaxis()->SetNdivisions(505);

      std::cout << "Outputting to: " << outPath << std::endl;

      canvas->SaveAs(Form("%s/%s_%s.png", outPath.c_str(), var.c_str(), effName.c_str()), "png");
    };
  };
};

