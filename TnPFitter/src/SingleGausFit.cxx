#include "TnPFitter/SingleGausFit.h"

#include <TCanvas.h>
#include <TLine.h>
#include <TF1.h>
#include <TH1F.h>
#include <Fit/ParameterSettings.h>

#include "JacobUtils/LoggingUtility.h"

#include "TnPFitter/FitConfig.h"
#include "TnPFitter/FitResult.h"

#include "TnPFitter/FitDrawingHelpers.h"

SingleGausFit::SingleGausFit(std::string name,
                             TH1F* histogram,
                             const FitConfig& fitConfig)
    : IFitter(name, {"SGaus"}, histogram, fitConfig) {
}

void SingleGausFit::SetBackgroundFunction() {
  testCompositeFunction();

  auto fullFunctionName = functionName + "_" + histogramName;
  auto formula = fitConfig.GetBackgroundFitFunction();

  backgroundFunction = new TF1(fullFunctionName.c_str(),
                               formula.c_str(),
                               bottomFitLimit,
                               topFitLimit);

  SetBackgroundFunctionParameters();
}

void SingleGausFit::SetBackgroundFunctionParameters() {
  std::vector<std::string> parameterNames = { "Constant", "Slope", "Poly" };

  for (auto parIdx = 0ul; parIdx < parameterNames.size(); parIdx++) {
    auto paramaterName = parameterNames[parIdx].c_str();
    auto value = compositeFunction->GetParameter(paramaterName);
    backgroundFunction->FixParameter(parIdx, value);
  }
}

void SingleGausFit::SetSignalFunction() {
  testCompositeFunction();

  auto fullFunctionName = functionName + "_signal_" + histogramName;
  auto formula = fitConfig.GetSignalFitFunction();

  signalFunction = new TF1(fullFunctionName.c_str(),
                           formula.c_str(),
                           bottomFitLimit,
                           topFitLimit);

  signalFunction->SetParNames("Gaus N", "Gaus Mean", "Gaus Sigma");

  signalFunction->FixParameter(0, compositeFunction->GetParameter("Gaus N"));
  signalFunction->FixParameter(1, compositeFunction->GetParameter("Gaus Mean"));
  signalFunction->FixParameter(2,
                               compositeFunction->GetParameter("Gaus Sigma"));
}

void SingleGausFit::SetCompositeUpFunction(void) {
  testCompositeFunction();

  SetCompositeUpComponent();

  histogram->Fit(compositeUpFunction, fitConfig.GetFitOptions().c_str());

  SetBackgroundUpFunction();
}

void SingleGausFit::SetCompositeUpComponent() {
  auto fullFunctionName = functionName + "_Composite_Up_" + histogramName;
  auto formula = fitConfig.GetFitFunction();

  compositeUpFunction = new TF1(fullFunctionName.c_str(),
                                formula.c_str(),
                                bottomFitLimit,
                                topFitLimit);

  auto constant = fitResult.getParameterUpVariation("Constant");
  auto slope = fitResult.getParameterDownVariation("Slope");
  auto poly = fitResult.getParameterUpVariation("Poly");

  SetCompositeErrFunction(compositeUpFunction, poly, slope, constant);
}

void SingleGausFit::SetBackgroundUpFunction() {
  auto fullFunctionName = functionName + "_Bkg_Up_" + histogramName;
  auto formula = fitConfig.GetBackgroundFitFunction();

  backgroundUpFunction = new TF1(fullFunctionName.c_str(),
                                 formula.c_str(),
                                 bottomFitLimit,
                                 topFitLimit);

  backgroundUpFunction->SetParameter(0, compositeUpFunction->GetParameter(3));
  backgroundUpFunction->SetParameter(1, compositeUpFunction->GetParameter(4));
  backgroundUpFunction->SetParameter(2, compositeUpFunction->GetParameter(5));
}

void SingleGausFit::SetCompositeDownFunction() {
  testCompositeFunction();

  SetCompositeDownComponent();

  histogram->Fit(compositeDownFunction, fitConfig.GetFitOptions().c_str());

  SetBackgroundDownFunction();
}

void SingleGausFit::SetCompositeDownComponent() {
  auto fullFunctionName = functionName + "_Composite_Down_" + histogramName;

  auto formula = fitConfig.GetFitFunction();

  compositeDownFunction = new TF1(fullFunctionName.c_str(),
                                  formula.c_str(),
                                  bottomFitLimit,
                                  topFitLimit);

  auto constant = fitResult.getParameterDownVariation("Constant");
  auto slope = fitResult.getParameterUpVariation("Slope");
  auto poly = fitResult.getParameterDownVariation("Poly");

  SetCompositeErrFunction(compositeDownFunction, poly, slope, constant);
}

void SingleGausFit::SetBackgroundDownFunction() {
  auto bkgFunctionName = functionName + "_Bkg_Down_" + histogramName;
  auto bkgFunction = fitConfig.GetBackgroundFitFunction();

  backgroundDownFunction = new TF1(bkgFunctionName.c_str(),
                                   bkgFunction.c_str(),
                                   bottomFitLimit,
                                   topFitLimit);

  backgroundDownFunction->SetParameter(0,
                                       compositeDownFunction->GetParameter(3));
  backgroundDownFunction->SetParameter(1,
                                       compositeDownFunction->GetParameter(4));
  backgroundDownFunction->SetParameter(2,
                                       compositeDownFunction->GetParameter(5));
}

void SingleGausFit::SetCompositeErrFunction(TF1* function,
                                            double poly,
                                            double slope,
                                            double constant) {
  auto nSignalParameters = 3;
  for (auto parIdx = 0; parIdx != nSignalParameters; parIdx++) {
    setupFunctionParameter(function, parIdx);
  }

  function->FixParameter(3, constant);
  function->FixParameter(4, slope);
  function->FixParameter(5, poly);
}

std::pair<double, double> SingleGausFit::GetSigmaAndMu() {
  auto mu = compositeFunction->GetParameter(1);
  auto sigma = compositeFunction->GetParameter(2);

  return (std::make_pair(sigma, mu));
}

FitConfig TNPFITTER::BuildSingleGausFitConfiguration(TH1* histogram,
                                                     double min,
                                                     double max) {
  if (histogram == nullptr) {
    throw(std::runtime_error("Histogram is not setup properly"));
  }

  Parameters pars = {
      {"Gaus N", histogram->GetMaximum(), 0, 0.0001, 10000000},
      {"Gaus Mean", 3.097, 0, 2.8, 3.3},
      {"Gaus Sigma", 0.1, 0, 0.02, 0.2},
  };

  auto polyPlusSingleGaus = "gaus(0) + [3] + [4] * x + [5] * x * x";
  auto singleGaus = "gaus(0)";
  auto poly = "[0] + [1] * x + [2] * x * x";

  FitConfig* fitConfig = new FitConfig(polyPlusSingleGaus, 6, min, max);

  pars.push_back({"Constant", 0});
  pars.push_back({"Slope", 0});
  pars.push_back({"Poly", 0});

  fitConfig->SetSignalFitFunction(singleGaus);
  fitConfig->SetBackgroundFitFunction(poly);
  fitConfig->SetParamsSettings(pars);
  fitConfig->SetFitOptions("MERBQN");

  return (*fitConfig);
}
