#include "TnPFitter/DoubleGausFit.h"
#include "TnPFitter/FitDrawingHelpers.h"

#include "JacobUtils/LoggingUtility.h"

#include "TCanvas.h"
#include "TLine.h"

#include "TnPFitter/BackgroundFittedFunction.h"
#include "TnPFitter/SignalFittedFunction.h"

#ifdef __CINT__
ClassImp(DoubleGausFit);
#endif

DoubleGausFit::DoubleGausFit(std::string val_name,
                             TH1F* val_histogram,
                             const FitConfig& val_fitConfig)
    : IFitter(val_name, {"DGaus"}, val_histogram, val_fitConfig) {
}

void DoubleGausFit::SetBackgroundFunction() {
  background = new BackgroundFittedFunction(name, histogramName, fitConfig);
  background->setParameterNames({"Constant", "Slope", "Poly"});
  background->setParametersFromFunction(compositeFunction);
}

void DoubleGausFit::SetSignalFunction() {
  testCompositeFunction();

  signal = new SignalFittedFunction(functionName, histogramName, fitConfig);
  signal->setParameterNames({"Narrow N",
                             "Narrow Mean",
                             "Narrow Sigma",
                             "Wide N",
                             "Wide Mean",
                             "Wide Sigma"});
  signal->setParametersFromFunction(compositeFunction);
}

void DoubleGausFit::SetCompositeUpFunction() {
  testCompositeFunction();
  SetCompositeUpComponent();

  histogram->Fit(compositeUpFunction, fitConfig.GetFitOptions().c_str());
  SetBackgroundUpFunction();
}

void DoubleGausFit::SetCompositeUpComponent() {
  auto funcNameComp = functionName + "_Composite_Up_" + histogramName;
  compositeUpFunction = new TF1(funcNameComp.c_str(),
                                fitConfig.GetFitFunction().c_str(),
                                bottomFitLimit,
                                topFitLimit);

  auto constant = fitResult.getParameterUpVariation("Constant");
  auto slope = fitResult.getParameterDownVariation("Slope");
  auto poly = fitResult.getParameterUpVariation("Poly");

  SetCompositeErrFunction(compositeUpFunction, poly, slope, constant);
}

void DoubleGausFit::SetBackgroundUpFunction() {
  auto funcNameBkg = functionName + "_Bkg_Up_" + histogramName;
  backgroundUpFunction = new TF1(funcNameBkg.c_str(),
                                 fitConfig.GetBackgroundFitFunction().c_str(),
                                 bottomFitLimit,
                                 topFitLimit);

  backgroundUpFunction->SetParameter(0, compositeUpFunction->GetParameter(6));
  backgroundUpFunction->SetParameter(1, compositeUpFunction->GetParameter(7));
  backgroundUpFunction->SetParameter(2, compositeUpFunction->GetParameter(8));
}

void DoubleGausFit::SetCompositeDownFunction() {
  testCompositeFunction();

  SetCompositeDownComponent();

  histogram->Fit(compositeDownFunction, fitConfig.GetFitOptions().c_str());
  SetBackgroundDownFunction();
}

void DoubleGausFit::SetCompositeDownComponent() {
  auto funcNameComp = functionName + "_Composite_Down_" + histogramName;

  compositeDownFunction = new TF1(funcNameComp.c_str(),
                                  fitConfig.GetFitFunction().c_str(),
                                  bottomFitLimit,
                                  topFitLimit);

  auto constant = fitResult.getParameterDownVariation("Constant");
  auto slope = fitResult.getParameterUpVariation("Slope");
  auto poly = fitResult.getParameterDownVariation("Poly");

  SetCompositeErrFunction(compositeDownFunction, poly, slope, constant);
}

void DoubleGausFit::SetBackgroundDownFunction() {
  auto funcNameBkg = functionName + "_Bkg_Down_" + histogramName;

  backgroundDownFunction = new TF1(funcNameBkg.c_str(),
                                   fitConfig.GetBackgroundFitFunction().c_str(),
                                   bottomFitLimit,
                                   topFitLimit);

  backgroundDownFunction->SetParameter(0,
                                       compositeDownFunction->GetParameter(6));
  backgroundDownFunction->SetParameter(1,
                                       compositeDownFunction->GetParameter(7));
  backgroundDownFunction->SetParameter(2,
                                       compositeDownFunction->GetParameter(8));
}

void DoubleGausFit::SetCompositeErrFunction(TF1* function,
                                            double poly,
                                            double slope,
                                            double constant) {
  auto nSignalParameters = 6;
  for (auto parIndex = 0; parIndex < nSignalParameters; parIndex++) {
    setupFunctionParameter(function, parIndex);
  }

  function->FixParameter(6, constant);
  function->FixParameter(7, slope);
  function->FixParameter(8, poly);
}

std::pair<double, double> DoubleGausFit::GetSigmaAndMu() {
  return (std::make_pair(GetSigma(), GetMu()));
}

double DoubleGausFit::GetSigma() {
  auto sigmaNarrow = compositeFunction->GetParameter(2);
  auto sigmaWide = compositeFunction->GetParameter(5);
  return ((sigmaWide + sigmaNarrow) / 2);
}

double DoubleGausFit::GetMu() {
  auto mass = fitConfig.ParSettings(1).Value();

  auto muNarrow = compositeFunction->GetParameter(1);
  auto muWide = compositeFunction->GetParameter(4);

  auto diffMuNarrow = fabs(mass - muNarrow);
  auto diffMuWide = fabs(mass - muWide);

  auto mu = 0.0f;

  if (diffMuWide < diffMuNarrow) {
    mu = muWide;
  } else {
    mu = muNarrow;
  }

  return (mu);
}

FitConfig TNPFITTER::BuildFitConfiguration(TH1* histogram,
                                           double min,
                                           double max) {
  auto polyPlusDoubleGaus = "gaus(0) + gaus(3) + [6] + [7] * x + [8] * x * x";
  auto doubleGaus = "gaus(0) + gaus(3)";
  auto poly = "[0] + [1] * x + [2] * x * x";

  auto config = FitConfig{polyPlusDoubleGaus, 9, min, max};
  config.SetFitOptions("MERBQN");
  config.SetSignalFitFunction(doubleGaus);
  config.AddParameter(
      {"Narrow N", histogram->GetMaximum(), 0, 0.0001, 1000000});
  config.AddParameter({"Narrow Mean", 3.097, 0, 2.8, 3.3});
  config.AddParameter({"Narrow Sigma", 0.1, 0, 0.02, 0.2});
  config.AddParameter(
      {"Wide N", histogram->GetMaximum(), 0, 0.0001, 10000000});
  config.AddParameter({"Wide Mean", 3.097, 0, 2.7, 3.4});
  config.AddParameter({"Wide Sigma", 0.3, 0, 0.08, 0.7});
  config.SetBackgroundFitFunction(poly);
  config.AddParameter({"Constant", 0});
  config.AddParameter({"Slope", 0});
  config.AddParameter({"Poly", 0});

  return (config);
}
