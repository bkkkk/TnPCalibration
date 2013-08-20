// self include
#include "TnPFitter/SingleGausFit.h"

// RootCore Cutsoms
#include "JacobUtils/LoggingUtility.h"

// Root
#include "TCanvas.h"
#include "TLine.h"
#include "TF1.h"
#include "TH1F.h"

//______________________________________________________________________________
SingleGausFit::
SingleGausFit(const std::string& name, TH1F* histogram, const FitConfig& fitConfig)
 : FitInterface(name, histogram, fitConfig)
{
  LOG_DEBUG3() << "Constructing a Single Gaus Fit";
  functionName = "SGaus";
}

//______________________________________________________________________________
SingleGausFit::
~SingleGausFit(void)
{

}

//______________________________________________________________________________
void SingleGausFit::
SetBackgroundFunction(void)
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
void SingleGausFit::
SetSignalFunction(void)
{
  // Test if the composite fit was done correctly
  testCompositeFunction();

  // Unique function name
  std::string funcName = functionName + "_signal_" + histogramName;

  // Create a background function
  signalFunction = new TF1( funcName.c_str(), fitConfig.GetSignalFitFunction().c_str(),
                            bottomFitLimit, topFitLimit );

  // Fit parameters of function
  signalFunction->FixParameter( 0, compositeFunction->GetParameter("Gaus N") );
  signalFunction->FixParameter( 1, compositeFunction->GetParameter("Gaus Mean") );
  signalFunction->FixParameter( 2, compositeFunction->GetParameter("Gaus Sigma") );
}

//______________________________________________________________________________
void SingleGausFit::
SetCompositeUpFunction (void)
{
  testCompositeFunction();

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

    backgroundUpFunction->SetParameter(0, compositeUpFunction->GetParameter(6));
    backgroundUpFunction->SetParameter(1, compositeUpFunction->GetParameter(7));
    backgroundUpFunction->SetParameter(2, compositeUpFunction->GetParameter(8));

    LOG_DEBUG1() << "Constant = " << backgroundUpFunction->GetParameter(0);
    LOG_DEBUG1() << "Slope = " << backgroundUpFunction->GetParameter(1);
    LOG_DEBUG1() << "Poly = " << backgroundUpFunction->GetParameter(2);
  }
}

//______________________________________________________________________________
void SingleGausFit::
SetCompositeDownFunction (void)
{
  testCompositeFunction();

  std::string funcNameComp = functionName + "_Composite_Down_" + histogramName;
  std::string funcNameBkg = functionName + "_Bkg_Down_" + histogramName;

  backgroundDownFunction = new TF1( funcNameBkg.c_str(), fitConfig.GetBackgroundFitFunction().c_str(),
                                    bottomFitLimit, topFitLimit );

  compositeDownFunction = new TF1( funcNameComp.c_str(), fitConfig.GetFitFunction().c_str(),
                                   bottomFitLimit, topFitLimit );

  if(fitConfig.GetMode() == 0)
  {
    double constant = fitResult->GetParValue("Constant") - fitResult->GetParError("Constant");
    double slope = fitResult->GetParValue("Slope") + fitResult->GetParError("Slope");
    double poly = fitResult->GetParValue("Poly") - fitResult->GetParError("Poly");

    SetCompositeErrFunction(compositeDownFunction, poly, slope, constant);

    histogram->Fit(compositeDownFunction, fitConfig.GetFitOptions().c_str());

    backgroundDownFunction->SetParameter(0, compositeDownFunction->GetParameter(6));
    backgroundDownFunction->SetParameter(1, compositeDownFunction->GetParameter(7));
    backgroundDownFunction->SetParameter(2, compositeDownFunction->GetParameter(8));

    LOG_DEBUG3() << "After fit";
    LOG_DEBUG3() << "Constant = " << backgroundDownFunction->GetParameter(0);
    LOG_DEBUG3() << "Slope = " << backgroundDownFunction->GetParameter(1);
    LOG_DEBUG3() << "Poly = " << backgroundDownFunction->GetParameter(2);
  }
}

//______________________________________________________________________________
void SingleGausFit::
SetCompositeErrFunction(TF1* function, double poly, double slope, double constant)
{
  LOG_DEBUG3() << "Setting parameters";
  LOG_DEBUG3() << "N Parameters: " << function->GetNpar();

  // Set up signal parameters for composite fit variation function
  for(int parIdx = 0; parIdx != 3; parIdx++)
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

  LOG_DEBUG3() << "Setting background variables";
  function->FixParameter(3, constant);
  function->FixParameter(4, slope);
  function->FixParameter(5, poly);
}

//______________________________________________________________________________
void SingleGausFit::
GetSigmaAndMu(double& sigma, double& mu)
{
  mu = compositeFunction->GetParameter(1);
  sigma = compositeFunction->GetParameter(2);

  LOG_DEBUG3() << "Gaus Mu = " << mu << ", Gaus Sigma = " << sigma;
}

//______________________________________________________________________________
FitConfig TNPFITTER::
BuildSingleGausFitConfiguration(TH1* histogram)
{
  // @todo remove magic numbers
  double min = 2.63;
  double max = 3.5;

  int bin = histogram->FindBin(min);
  std::vector<ROOT::Fit::ParameterSettings> pars;

  pars.push_back( ROOT::Fit::ParameterSettings("Gaus N", histogram->GetMaximum(), 0, 0.0001, 10000000));
  pars.push_back( ROOT::Fit::ParameterSettings("Gaus Mean", 3.097, 0, 2.8, 3.3) );
  pars.push_back( ROOT::Fit::ParameterSettings("Gaus Sigma", 0.1, 0, 0.02, 0.2) );

  std::string polyPlusSingleGaus = "gaus(0) + [3] + [4] * x + [5] * x * x";
  std::string singleGaus = "gaus(0)";
  std::string poly = "[0] + [1] * x + [2] * x * x";

  FitConfig* fitConfig;

  double testValue = histogram->GetBinContent( bin );

  // @todo remove magic numbers
  if(histogram->GetMaximum() * 0.07 > testValue)
  {
    LOG_DEBUG() << "====> LOW BACKGROUND MODE ====";
    fitConfig = new FitConfig(singleGaus, 3, true, min, max);
  }
  else
  {
    LOG_DEBUG() << "====> HIGH BACKGROUND MODE ====";
    fitConfig = new FitConfig(polyPlusSingleGaus, 6, false, min, max);

    pars.push_back( ROOT::Fit::ParameterSettings("Constant", 0) );
    pars.push_back( ROOT::Fit::ParameterSettings("Slope", 0) );
    pars.push_back( ROOT::Fit::ParameterSettings("Poly", 0) );
  }

  fitConfig->SetSignalFitFunction(singleGaus);
  fitConfig->SetBackgroundFitFunction(poly);
  fitConfig->SetParamsSettings(pars);
  fitConfig->SetFitOptions("MERBQN");

  return(*fitConfig);
}
