// Self inclusion
#include "TnPFitter/FitterDraw.h"

#include <iostream>

// ROOT
#include <TFile.h>
#include <TLine.h>
#include <TF1.h>
#include <TH1F.h>
#include <TCanvas.h>

//______________________________________________________________________________
FitterDraw::
FitterDraw(FitInterface* fitter, int sigma, int window)
 : fFitter(fitter),
   fSigma(sigma),
   fWindow(window)
{
  configFile = TFile::Open("$ROOTCOREDIR/data/TnPFitter/TnPFitter-FittingConfig.xml", "OPEN");
  
  if(configFile->IsZombie() == 1)
  {
    LOG_ERROR() << "Failed to load configuration XML file";
    throw;
  }

  LOG_INFO() << "Loading line configuration file";

  configFile->GetObject("BkgUpConfig", bkgUp);
  configFile->GetObject("BkgDownConfig", bkgDown);
  configFile->GetObject("BkgConfig", bkg);
  configFile->GetObject("SignalConfig", signal);
  configFile->GetObject("NominalConfig", nominal);

  configFile->Close();

  LOG_INFO() << "Loding succesfully completed";

  if(fFitter == NULL)
  {
    LOG_ERROR() << "Fitter object is not configured correctly";
    throw;
  }

  TH1* histogram = fFitter->GetHistogram();

  histMin = histogram->GetMinimum() - histogram->GetMaximum() * 0.05;
  histMax = histogram->GetMaximum() * 1.2;

  LOG_DEBUG1() << "Histogram min: " << histMin << " max: " << histMax;
}

//______________________________________________________________________________
FitterDraw::
~FitterDraw(void)
{

}

//______________________________________________________________________________
void FitterDraw::
SetupLines(const std::string& options)
{
  // Set up function
  SetupLine(fFitter->GetSignalFunction(), signal);
  SetupLine(fFitter->GetBackgroundFunction(), bkg);
  SetupLine(fFitter->GetCompositeFunction(), nominal);
  SetupLine(fFitter->GetBackgroundUpFunction(), bkgUp);
  SetupLine(fFitter->GetBackgroundDownFunction(), bkgDown);

  // Get Ranges
  float narrowSigmaLow = fFitter->GetSigmaLow(fSigma);
  float narrowSigmaHigh = fFitter->GetSigmaHigh(fSigma);
  float wideSigmaLow = fFitter->GetSigmaLow(fSigma + fWindow);
  float wideSigmaHigh = fFitter->GetSigmaHigh(fSigma + fWindow);

  // Set up lines
  fiveLow = new TLine  ( wideSigmaLow,    histMin, wideSigmaLow,    histMax );
  fiveHigh = new TLine ( wideSigmaHigh,   histMin, wideSigmaHigh,   histMax );
  threeLow = new TLine ( narrowSigmaLow,  histMin, narrowSigmaLow,  histMax );
  threeHigh = new TLine( narrowSigmaHigh, histMin, narrowSigmaHigh, histMax );

  fiveLow->SetLineColor(3); fiveLow->SetLineWidth(2);
  fiveHigh->SetLineColor(3); fiveHigh->SetLineWidth(2);
  
  threeLow->SetLineColor(6); threeLow->SetLineWidth(2);
  threeHigh->SetLineColor(6); threeHigh->SetLineWidth(2);
}

//______________________________________________________________________________
void FitterDraw::
Draw(const std::string& options)
{
  // Setup the lines
  SetupLines(options);

  // Canvas and other thingies
  std::string name = fFitter->GetName();
  TCanvas* c1 = new TCanvas(name.c_str(), name.c_str(), 0, 0, 800, 600);
  TH1* histogram = fFitter->GetHistogram();
  histogram->GetYaxis()->SetRangeUser(histMin, histMax);

  // Canvas + histogram
  c1->Draw();
  histogram->Draw();
  
  // Draw function
  fFitter->GetCompositeFunction()->Draw("SAME");
  if(fFitter->GetFitConfig().GetMode() != 1)
  {
    fFitter->GetBackgroundFunction()->Draw("SAME");
    fFitter->GetSignalFunction()->Draw("SAME");
    fFitter->GetBackgroundDownFunction()->Draw("SAME");
    fFitter->GetBackgroundUpFunction()->Draw("SAME");
  }

  fiveLow->Draw(); fiveHigh->Draw();
  threeLow->Draw(); threeHigh->Draw();

  std::string filename = fFitter->GetFunctionName() + "-" + histogram->GetName() + ".pdf";
  c1->SaveAs(filename.c_str(), "pdf");
  c1->Close();
}

//______________________________________________________________________________
void FitterDraw::
SetupLine(TF1* line, LineAttrib* attribute)
{
  if(line == NULL)
  {
    LOG_WARNING() << "Function of line not setup correctly";
    return;
  }

  LOG_INFO() << "Setting up line: " << attribute->name;
  
  // Setup the line
  line->SetLineColor(attribute->color);
  line->SetLineWidth(attribute->width);
  line->SetLineStyle(attribute->style);
  // @BUG :: Npx value not saved to the XML file
  line->SetNpx(1000);

  return;
}

ClassImp(FitterDraw)
