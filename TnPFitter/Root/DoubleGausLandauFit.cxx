#include "TnPFitter/DoubleGausLandauFit.h"
#include "JacobUtils/LoggingUtility.h"

#include <TLine.h>
#include <TCanvas.h>

//______________________________________________________________________________
DoubleGausLandauFit::
DoubleGausLandauFit( const std::string& val_name,
                     TH1F* val_histogram,
                     const FitConfig& val_fitConfig)
 : FitInterface(val_name, val_histogram, val_fitConfig)
{
  LOG_DEBUG() << "Constructing a double gaus + landau fit";
  functionName = "LandGaus";
}

//______________________________________________________________________________
DoubleGausLandauFit::
~DoubleGausLandauFit()
{

}

//______________________________________________________________________________
void DoubleGausLandauFit::
SetSignalFunction (void)
{
  testCompositeFunction();

  std::string funcName = functionName + "_signal_" + histogramName;

  // Setup signal function
  signalFunction = new TF1( funcName.c_str(), fitConfig.GetSignalFitFunction().c_str(),
                            bottomFitLimit, topFitLimit );

  signalFunction->FixParameter(0, compositeFunction->GetParameter("Gaus N"));
  signalFunction->FixParameter(1, compositeFunction->GetParameter("Gaus Mean"));
  signalFunction->FixParameter(2, compositeFunction->GetParameter("Gaus Sigma"));
  signalFunction->FixParameter(3, compositeFunction->GetParameter("Landau MPV"));
  signalFunction->FixParameter(4, compositeFunction->GetParameter("Landau Sigma"));

  return;
}

//______________________________________________________________________________
void DoubleGausLandauFit::
SetBackgroundFunction (void)
{
  testCompositeFunction();

  std::string funcName = functionName + "_" + histogramName;

  backgroundFunction = new TF1( funcName.c_str(), fitConfig.GetBackgroundFitFunction().c_str(),
                                bottomFitLimit, topFitLimit);

  // Create a background function
  if(fitConfig.GetMode() != 1)
  {
    backgroundFunction->FixParameter(0, compositeFunction->GetParameter("Constant"));
    backgroundFunction->FixParameter(1, compositeFunction->GetParameter("Slope"));
    backgroundFunction->FixParameter(2, compositeFunction->GetParameter("Poly"));
  }

  return;
}

//______________________________________________________________________________
void DoubleGausLandauFit::
SetCompositeUpFunction (void)
{
  testCompositeFunction();

  LOG_DEBUG() << "SetCompositeUpFunction :: ";

  std::string funcNameComp = functionName + "_Composite_Up_" + histogramName;
  std::string funcNameBkg = functionName + "_Bkg_Up_" + histogramName;

  backgroundUpFunction = new TF1( funcNameBkg.c_str(), fitConfig.GetBackgroundFitFunction().c_str(),
                                  bottomFitLimit, topFitLimit );

  compositeUpFunction = new TF1( funcNameComp.c_str(), fitConfig.GetFitFunction().c_str(), 
                                  bottomFitLimit, topFitLimit );

  if(fitConfig.GetMode() != 1)
  {    
    double constant = fitResult->GetParValue("Constant") + fitResult->GetParError("Constant");
    double slope = fitResult->GetParValue("Slope") - fitResult->GetParError("Slope");
    double poly = fitResult->GetParValue("Poly") + fitResult->GetParError("Poly");
    
    SetCompositeErrFunction(compositeUpFunction, poly, slope, constant);

    histogram->Fit(compositeUpFunction, fitConfig.GetFitOptions().c_str());


    backgroundUpFunction->SetParameter(0, compositeUpFunction->GetParameter(5));
    backgroundUpFunction->SetParameter(1, compositeUpFunction->GetParameter(6));
    backgroundUpFunction->SetParameter(2, compositeUpFunction->GetParameter(7));

    LOG_DEBUG1() << "After fit";
    LOG_DEBUG1() << "Constant = " << backgroundUpFunction->GetParameter(0);
    LOG_DEBUG1() << "Slope = " << backgroundUpFunction->GetParameter(1);
    LOG_DEBUG1() << "Poly = " << backgroundUpFunction->GetParameter(2);
  }
}

//______________________________________________________________________________
void DoubleGausLandauFit::
SetCompositeDownFunction (void)
{
  testCompositeFunction();

  LOG_DEBUG() << "SetCompositeDownFunction :: ";

  std::string funcNameComp = functionName + "_Composite_Down_" + histogramName;
  std::string funcNameBkg = functionName + "_Bkg_Down_" + histogramName;

  backgroundDownFunction = new TF1( funcNameBkg.c_str(), fitConfig.GetBackgroundFitFunction().c_str(),
                                  bottomFitLimit, topFitLimit );

  compositeDownFunction = new TF1( funcNameComp.c_str(), fitConfig.GetFitFunction().c_str(), 
                                  bottomFitLimit, topFitLimit );

  if(fitConfig.GetMode() != 1)
  {    
    double constant = fitResult->GetParValue("Constant") - fitResult->GetParError("Constant");
    double slope = fitResult->GetParValue("Slope") + fitResult->GetParError("Slope");
    double poly = fitResult->GetParValue("Poly") - fitResult->GetParError("Poly");
    
    SetCompositeErrFunction(compositeDownFunction, poly, slope, constant);

    histogram->Fit(compositeDownFunction, fitConfig.GetFitOptions().c_str());

    backgroundDownFunction->SetParameter(0, compositeDownFunction->GetParameter(5));
    backgroundDownFunction->SetParameter(1, compositeDownFunction->GetParameter(6));
    backgroundDownFunction->SetParameter(2, compositeDownFunction->GetParameter(7));

    LOG_DEBUG1() << "After fit";
    LOG_DEBUG1() << "Constant = " << backgroundDownFunction->GetParameter(0);
    LOG_DEBUG1() << "Slope = " << backgroundDownFunction->GetParameter(1);
    LOG_DEBUG1() << "Poly = " << backgroundDownFunction->GetParameter(2);
  }
}

//______________________________________________________________________________
void DoubleGausLandauFit::
SetCompositeErrFunction(TF1* function, double poly, double slope, double constant)
{
  LOG_DEBUG() << "Setting parameters";
  LOG_DEBUG() << "N Parameters: " << function->GetNpar();

  // Set up signal parameters for composite fit variation function
  for(int parIdx = 0; parIdx != 5; parIdx++)
  {
    double val = fitConfig.ParSettings(parIdx).Value();
    double min = fitConfig.ParSettings(parIdx).LowerLimit();
    double max = fitConfig.ParSettings(parIdx).UpperLimit();
    std::string namePar = fitConfig.ParSettings(parIdx).Name();

    LOG_DEBUG() << namePar << " :: " << val 
               << " min = " << min
               << ", max = " << max;

    function->SetParName( parIdx, namePar.c_str() );
    function->SetParameter( parIdx, val );
    
    if(fitConfig.ParSettings(parIdx).HasLowerLimit())
    {
      function->SetParLimits( parIdx, min, max );  
    }
  }

  // @todo fix this stupidity so that you can have a generic fitting algorithm
  LOG_DEBUG() << "Setting background variables";
  function->FixParameter(5, constant);
  function->FixParameter(6, slope);
  function->FixParameter(7, poly);

  return;
}

//______________________________________________________________________________
void DoubleGausLandauFit::
GetSigmaAndMu(double& sigma, double& mu)
{
  mu = compositeFunction->GetParameter("Gaus Mean");
  sigma = compositeFunction->GetParameter("Gaus Sigma");

  LOG_DEBUG2() << "Selected sigma = " << sigma << ", mu = " << mu;
} 

//______________________________________________________________________________
//_____ Convenience Functions __________________________________________________
//______________________________________________________________________________

FitConfig LANDAUFIT::
BuildFitConfiguration(TH1* histogram)
{
  // Pointer to configuration object
  FitConfig* fitConfig;

  // A hacky sort of way of finding whether this is low background or
  // high background
  int bin = histogram->FindBin(2.6);
  std::vector<ROOT::Fit::ParameterSettings> pars;

  double top = histogram->GetMaximum();

  // Gaussian fitting parameters
  std::string signalFunction = "gaus(0) + TMath::Landau(x, [3], [4])";
  pars.push_back( ROOT::Fit::ParameterSettings("Gaus N", top, 0, 0.0001, top + 1000) );
  pars.push_back( ROOT::Fit::ParameterSettings("Gaus Mean", 3.097, 0, 2.8, 3.3) );
  pars.push_back( ROOT::Fit::ParameterSettings("Gaus Sigma", 0.1, 0, 0.02, 0.2) );

  // Landau fitting parameters
  pars.push_back( ROOT::Fit::ParameterSettings("Landau MPV", 3.097) );
  pars.push_back( ROOT::Fit::ParameterSettings("Landau Sigma", 0.2) );

  std::string compositeFunction = "gaus(0) + TMath::Landau(x, [3], [4]) + [5] + [6] * x + [7] * x * x";

  std::string backgroundFunction = "[0] + [1] * x + [2] * x * x";

  // Background fitting parameters
  if(histogram->GetBinContent( bin ) < 10)
  { 
    LOG_DEBUG() << "====> LOW BACKGROUND MODE";
    fitConfig = new FitConfig(signalFunction, 5, true);
  } else
  {
    LOG_DEBUG() << "====> HIGH BACKGROUND MODE";
    fitConfig = new FitConfig(compositeFunction, 8, false);

    pars.push_back( ROOT::Fit::ParameterSettings("Constant", 0) );
    pars.push_back( ROOT::Fit::ParameterSettings("Slope", 0) );
    pars.push_back( ROOT::Fit::ParameterSettings("Poly", 0) ); 
  }

  fitConfig->SetSignalFitFunction(signalFunction);
  fitConfig->SetBackgroundFitFunction(backgroundFunction);
  fitConfig->SetParamsSettings(pars);
  fitConfig->SetFitOptions("MERBQN");

  return(*fitConfig);
}

// For CINT streamer support
ClassImp(DoubleGausLandauFit)

