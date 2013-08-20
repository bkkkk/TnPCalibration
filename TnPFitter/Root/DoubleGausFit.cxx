// Self
#include "TnPFitter/DoubleGausFit.h"

// RootCore Customs
#include "JacobUtils/LoggingUtility.h"

// Root
#include "TCanvas.h"
#include "TLine.h"

ClassImp(DoubleGausFit)

//________________________________________________________________________
DoubleGausFit::
DoubleGausFit(const std::string& val_name, TH1F* val_histogram, const FitConfig& val_fitConfig)
  : FitInterface(val_name, val_histogram, val_fitConfig)
{
  LOG_DEBUG3() << "Constructing a double gaus fit";
  functionName = "DGaus";
}

//________________________________________________________________________
DoubleGausFit::
~DoubleGausFit(void)
{

}

//______________________________________________________________________________
void DoubleGausFit::
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
    backgroundFunction->SetLineColor(6);
    backgroundFunction->SetLineStyle(7);
  }

  return;
}

//______________________________________________________________________________
void DoubleGausFit::
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
void DoubleGausFit::
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

  return;
}

//______________________________________________________________________________
void DoubleGausFit::
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

  return;
}

//______________________________________________________________________________
void DoubleGausFit::
SetCompositeErrFunction(TF1* function, double poly, double slope, double constant)
{
  LOG_DEBUG3() << "Setting parameters";
  LOG_DEBUG3() << "N Parameters: " << function->GetNpar();

  // Set up signal parameters for composite fit variation function
  for(int parIdx = 0; parIdx != 6; parIdx++)
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
  function->FixParameter(6, constant);
  function->FixParameter(7, slope);
  function->FixParameter(8, poly);

  return;
}

//______________________________________________________________________________
void DoubleGausFit::
GetSigmaAndMu(double& sigma, double& mu)
{
  double muNarrow = compositeFunction->GetParameter(1);
  double sigmaNarrow = compositeFunction->GetParameter(2);

  double muWide = compositeFunction->GetParameter(4);
  double sigmaWide = compositeFunction->GetParameter(5);

  if(fitConfig.GetMode() == 0)
  {
    sigma = (sigmaWide + sigmaNarrow) / 2;
  }
  else
  {
    if(sigmaNarrow < sigmaWide)
    {
      sigma = sigmaNarrow;
    }
    else
    {
      sigma = sigmaWide;
    }
  }

  double mass = fitConfig.ParSettings(1).Value();
  double diffMuNarrow = fabs(mass - muNarrow);
  double diffMuWide = fabs(mass - muWide);

  if(diffMuWide < diffMuNarrow)
  {
    mu = muWide;
  }
  else
  {
    mu = muNarrow;
  }

  LOG_DEBUG3() << "Mu Wide = " << muWide << ", Mu Narrow = " << muNarrow;
  LOG_DEBUG3() << "Selected sigma = " << sigma << ", mu = " << mu;

  return;
}

//______________________________________________________________________________
FitConfig TNPFITTER::
BuildFitConfiguration(TH1* histogram)
{
  // @todo remove magic numbers
  double min = 2.63;
  double max = 3.5;

  std::vector<ROOT::Fit::ParameterSettings> pars;

  pars.push_back( ROOT::Fit::ParameterSettings("Narrow N", histogram->GetMaximum(), 0, 0.0001, 10000000));
  pars.push_back( ROOT::Fit::ParameterSettings("Narrow Mean", 3.097, 0, 2.8, 3.3) );
  pars.push_back( ROOT::Fit::ParameterSettings("Narrow Sigma", 0.1, 0, 0.02, 0.2) );

  pars.push_back( ROOT::Fit::ParameterSettings("Wide N", histogram->GetMaximum(), 0, 0.0001, 10000000));
  pars.push_back( ROOT::Fit::ParameterSettings("Wide Mean", 3.097, 0, 2.7, 3.4) );
  pars.push_back( ROOT::Fit::ParameterSettings("Wide Sigma", 0.3, 0, 0.08, 0.7) );

  std::string polyPlusDoubleGaus = "gaus(0) + gaus(3) + [6] + [7] * x + [8] * x * x";
  std::string doubleGaus = "gaus(0) + gaus(3)";
  std::string poly = "[0] + [1] * x + [2] * x * x";

  FitConfig* fitConfig;

  if(TNPFITTER::IsLowBackground(histogram, min, 0.07))
  {
    fitConfig = new FitConfig(doubleGaus, 6, true, min, max);
  }
  else
  {
    fitConfig = new FitConfig(polyPlusDoubleGaus, 9, false, min, max);

    pars.push_back( ROOT::Fit::ParameterSettings("Constant", 0) );
    pars.push_back( ROOT::Fit::ParameterSettings("Slope", 0) );
    pars.push_back( ROOT::Fit::ParameterSettings("Poly", 0) );
  }

  fitConfig->SetSignalFitFunction(doubleGaus);
  fitConfig->SetBackgroundFitFunction(poly);
  fitConfig->SetParamsSettings(pars);
  fitConfig->SetFitOptions("MERBQN");

  return(*fitConfig);
}
