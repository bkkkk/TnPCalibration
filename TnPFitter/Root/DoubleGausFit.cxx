// Self
#include "TnPFitter/DoubleGausFit.h"

// RootCore Customs
#include "JacobUtils/LoggingUtility.h"

// Root
#include "TCanvas.h"
#include "TLine.h"

//________________________________________________________________________
DoubleGausFit::
DoubleGausFit(const std::string& val_name, TH1F* val_histogram, const FitConfig& val_fitConfig)
 : name(val_name),
   fitConfig(val_fitConfig),
   histogram(val_histogram),
   bottomFitLimit(2.6),
   topFitLimit(3.5),
   fitResult( new FitResult ( name, 9 ) )
{

}

//________________________________________________________________________
DoubleGausFit::
~DoubleGausFit(void)
{
  delete compositeFunction;
  delete backgroundFunction;
  delete signalFunction;
}

//________________________________________________________________________
void DoubleGausFit::
fitCompositeFunction()
{
  std::string nameOfFunc = "Fitter_" + std::string(histogram->GetName());

  LOG_INFO() << "Fitting: " << histogram->GetName();

  fLowMode = fitConfig.GetMode();

	compositeFunction = new TF1( nameOfFunc.c_str(), fitConfig.GetFitFunction().c_str(),
                               bottomFitLimit, topFitLimit );

  for(int parIdx = 0; parIdx != compositeFunction->GetNpar(); parIdx++)
  {
    double val = fitConfig.ParSettings(parIdx).Value();
    double min = fitConfig.ParSettings(parIdx).LowerLimit();
    double max = fitConfig.ParSettings(parIdx).UpperLimit();
    std::string namePar = fitConfig.ParSettings(parIdx).Name();

  	compositeFunction->SetParName( parIdx, namePar.c_str() );
    compositeFunction->SetParameter( parIdx, val );

    if(fitConfig.ParSettings(parIdx).HasLowerLimit())
    {
      compositeFunction->SetParLimits( parIdx, min, max );
    }
  }
  
	histogram->Fit(compositeFunction, fitConfig.GetFitOptions().c_str());

  // Set Parameter results
  for(int parIdx = 0; parIdx != compositeFunction->GetNpar(); parIdx++)
  {
    std::string parName = compositeFunction->GetParName(parIdx);
    float parValue = compositeFunction->GetParameter(parIdx);
    float parError = compositeFunction->GetParError(parIdx);

    fitResult->AddParameter(parName, parValue, parError);
  };

	return;
}

//______________________________________________________________________________
void DoubleGausFit::
setBackgroundFunction(void)
{
  if(compositeFunction == NULL)
  {
    LOG_INFO() << "Composite function not set and fit not run";
    LOG_INFO() << "Running fit now";
    fitCompositeFunction();
  }

  // Create a background function
  std::string poly = "[0] + [1] * x + [2] * x * x";
  backgroundFunction = new TF1("Poly", poly.c_str(), bottomFitLimit, topFitLimit);

  backgroundFunction->FixParameter(0, compositeFunction->GetParameter("Constant"));
  backgroundFunction->FixParameter(1, compositeFunction->GetParameter("Slope"));
  backgroundFunction->FixParameter(2, compositeFunction->GetParameter("Poly"));

  backgroundFunction->SetLineColor(6); backgroundFunction->SetLineStyle(7);

  return;
}

//______________________________________________________________________________
void DoubleGausFit::
setSignalFunction(void)
{
  if(compositeFunction == NULL)
  {
    LOG_INFO() << "Composite function not set and fit not run";
    LOG_INFO() << "Running fit now";
    fitCompositeFunction();
  }

  // Create a background function
  std::string doubleGaus = "gaus(0) + gaus(3)";
  signalFunction = new TF1("DoubleGaus", doubleGaus.c_str(), bottomFitLimit, topFitLimit);

  signalFunction->FixParameter( 0, compositeFunction->GetParameter("Narrow N") );
  signalFunction->FixParameter( 1, compositeFunction->GetParameter("Narrow Mean") );
  signalFunction->FixParameter( 2, compositeFunction->GetParameter("Narrow Sigma") );
  signalFunction->FixParameter( 3, compositeFunction->GetParameter("Wide N") );
  signalFunction->FixParameter( 4, compositeFunction->GetParameter("Wide Mean") );
  signalFunction->FixParameter( 5, compositeFunction->GetParameter("Wide Sigma") );

  signalFunction->SetLineColor(kRed);

  return;
}

//______________________________________________________________________________
TF1* DoubleGausFit::
GetCompositeFunction()
{
  testCompositeFunction();

  return (compositeFunction);
}

//______________________________________________________________________________
TF1* DoubleGausFit::
GetSignalFunction()
{
  testSignalFunction();

  return (signalFunction);
}

//______________________________________________________________________________
TF1* DoubleGausFit::
GetBackgroundFunction()
{
  testBackgroundFunction();
  return (backgroundFunction);
}

//______________________________________________________________________________
void DoubleGausFit::
setFitLimits(const double min, const double max)
{
  bottomFitLimit = min;
  topFitLimit = max;
  return;
}

//______________________________________________________________________________
// Need to implement these
double DoubleGausFit::
GetSignalIntegral(int sigma)
{
  if(histogram == NULL)
  {
    LOG_ERROR() << "Histogram is not configured properly";
    return (0);
  }

  int binMin = histogram->FindBin(GetSigmaLow(sigma));
  int binMax = histogram->FindBin(GetSigmaHigh(sigma));

  return( histogram->Integral(binMin, binMax) );
}

//______________________________________________________________________________
// Need to implement these
double DoubleGausFit::
GetBackgroundIntegral(int sigma)
{
  if(fLowMode != 0)
  {
    testBackgroundFunction();
  } else
  {
    return (0.0);
  }

  double lowLimit = GetSigmaLow(sigma);
  double highLimit = GetSigmaHigh(sigma);

  return(backgroundFunction->Integral(lowLimit, highLimit));
}


//______________________________________________________________________________
double DoubleGausFit::
GetSigmaLow(int nSigma)
{
  testCompositeFunction();
  
  double muNarrow = compositeFunction->GetParameter(1);
  double sigmaNarrow = compositeFunction->GetParameter(2);

  double muWide = compositeFunction->GetParameter(4);
  double sigmaWide = compositeFunction->GetParameter(5);

  double sigma;
  double mu;

  if(sigmaWide < sigmaNarrow)
  {
    sigma = sigmaNarrow;
    mu = muWide;
  } else
  {
    sigma = sigmaWide;
    mu = muNarrow;
  }

  return(mu - nSigma * sigma);
};

//______________________________________________________________________________
double DoubleGausFit::
GetSigmaHigh(int nSigma)
{
  testCompositeFunction();

  double muNarrow = compositeFunction->GetParameter(1);
  double sigmaNarrow = compositeFunction->GetParameter(2);

  double muWide = compositeFunction->GetParameter(4);
  double sigmaWide = compositeFunction->GetParameter(5);

  double sigma;
  double mu;

  if(sigmaWide < sigmaNarrow)
  {
    sigma = sigmaNarrow;
    mu = muWide;
  } else
  {
    sigma = sigmaWide;
    mu = muNarrow;
  }

  return(mu + nSigma * sigma);
};

//______________________________________________________________________________
void DoubleGausFit::
Draw()
{
	if(compositeFunction == NULL) return;

	TCanvas c1(name.c_str(), name.c_str(), 0, 0, 600, 800);
	c1.Draw();

  compositeFunction->SetNpx(1000);
  compositeFunction->SetLineColor(4);
  compositeFunction->SetLineStyle(9);
  compositeFunction->SetLineWidth(2.5);

  histogram->GetYaxis()->SetRangeUser(histogram->GetMinimum() - histogram->GetMaximum() * 0.05, histogram->GetMaximum() * 1.2);
	histogram->Draw();
	compositeFunction->Draw("SAME");

  float histMin = histogram->GetMaximum();
  float histMax = histogram->GetMinimum();

  LOG_INFO() << "Histogram min: " << histMin << " max: " << histMax;

  float threeSigmaLow = GetSigmaLow(3);
  float threeSigmaHigh = GetSigmaHigh(3);
  
  float fiveSigmaLow = GetSigmaLow(5);
  float fiveSigmaHigh = GetSigmaHigh(5);

  TLine* fiveLow = new TLine( fiveSigmaLow, histMin, fiveSigmaLow, histMax );
  TLine* fiveHigh = new TLine( fiveSigmaHigh, histMin, fiveSigmaHigh, histMax );
  TLine* threeLow = new TLine( threeSigmaLow, histMin, threeSigmaLow, histMax );
  TLine* threeHigh = new TLine( threeSigmaHigh, histMin, threeSigmaHigh, histMax );

  fiveLow->SetLineColor(3); fiveLow->SetLineWidth(2);
  fiveHigh->SetLineColor(3); fiveHigh->SetLineWidth(2);
  
  threeLow->SetLineColor(6); threeLow->SetLineWidth(2);
  threeHigh->SetLineColor(6); threeHigh->SetLineWidth(2);

  fiveLow->Draw(); fiveHigh->Draw();
  threeLow->Draw(); threeHigh->Draw();

  if(backgroundFunction != NULL)
  {
    backgroundFunction->SetNpx(1000);
    backgroundFunction->Draw("SAME");
  }
  
  if(signalFunction != NULL)
  {
    signalFunction->SetNpx(1000);
    signalFunction->Draw("SAME");
  }

  fiveLow->Draw(); fiveHigh->Draw(); threeLow->Draw(); threeHigh->Draw();

	std::string filename = name + "-" + histogram->GetName() + ".pdf";

	c1.SaveAs(filename.c_str(), "pdf");

	return;
}

//______________________________________________________________________________
FitConfig TNPFITTER::
BuildFitConfiguration(TH1* histogram)
{
  double lowLimits = 2.6;

  int bin = histogram->FindBin(lowLimits);
  LOG_INFO() << "Low limit: " << lowLimits << " in bin " << bin;
  std::vector<ROOT::Fit::ParameterSettings> pars;

  pars.push_back( ROOT::Fit::ParameterSettings("Narrow N", histogram->GetMaximum(), 0, 0.0001, 10000000));
  pars.push_back( ROOT::Fit::ParameterSettings("Narrow Mean", 3.097, 0, 2.8, 3.3) );
  pars.push_back( ROOT::Fit::ParameterSettings("Narrow Sigma", 0.1, 0, 0.02, 0.2) );
  
  pars.push_back( ROOT::Fit::ParameterSettings("Wide N", histogram->GetMaximum(), 0, 0.0001, 10000000));
  pars.push_back( ROOT::Fit::ParameterSettings("Wide Mean", 3.097, 0, 2.8, 3.3) );
  pars.push_back( ROOT::Fit::ParameterSettings("Wide Sigma", 0.2, 0, 0.05, 0.3) );

  std::string polyPlusDoubleGaus = "gaus(0) + gaus(3) + [6] + [7] * x + [8] * x * x";
  std::string doubleGaus = "gaus(0) + gaus(3)";
  std::string poly = "[0] + [1] * x + [2] * x * x";

  FitConfig* fitConfig;

  if(histogram->GetBinContent( bin ) < 10)
  { 
    LOG_INFO() << "====> LOW BACKGROUND MODE";
    fitConfig = new FitConfig(doubleGaus, 6, true);
  } else
  {
    LOG_INFO() << "====> HIGH BACKGROUND MODE";
    fitConfig = new FitConfig(polyPlusDoubleGaus, 9, false);
    pars.push_back( ROOT::Fit::ParameterSettings("Constant", 0) );
    pars.push_back( ROOT::Fit::ParameterSettings("Slope", 0) );
    pars.push_back( ROOT::Fit::ParameterSettings("Poly", 0) ); 
  };

  fitConfig->SetParamsSettings(pars);
  fitConfig->SetFitOptions("MERBQ");

  return(*fitConfig);
}

//______________________________________________________________________________
int TNPFITTER::
RunFit(DoubleGausFit* fitter)
{
  if(fitter == NULL)
  {
    return (1);
  }

  LOG_INFO() << "Running Fit";
  fitter->fitCompositeFunction();
  fitter->setSignalFunction();
  fitter->setBackgroundFunction();
  fitter->Draw();

  return (1);
}
