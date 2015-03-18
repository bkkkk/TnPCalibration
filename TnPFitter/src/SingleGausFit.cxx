#include "TnPFitter/SingleGausFit.h"

#include "JacobUtils/LoggingUtility.h"

#include <TF1.h>
#include <TH1F.h>

SingleGausFit::SingleGausFit(std::string name,
                             TH1F* histogram,
                             const FitConfig& fitConfig)
    : IFitter(name, {"SGaus"}, histogram, fitConfig) {
}

void SingleGausFit::SetBackgroundFunction() {
  GetBackgroundFunction()->FixParameter(
      0, GetCompositeFunction()->GetParameter("Constant"));
  GetBackgroundFunction()->FixParameter(
      1, GetCompositeFunction()->GetParameter("Slope"));
  GetBackgroundFunction()->FixParameter(
      2, GetCompositeFunction()->GetParameter("Poly"));
}

void SingleGausFit::SetSignalFunction() {
  signalFunction->FixParameter(0,
                               GetCompositeFunction()->GetParameter("Gaus N"));
  signalFunction->FixParameter(
      1, GetCompositeFunction()->GetParameter("Gaus Mean"));
  signalFunction->FixParameter(
      2, GetCompositeFunction()->GetParameter("Gaus Sigma"));
}

void SingleGausFit::SetCompositeUpComponent() {
  setCompositeSignalComponent(GetCompositeUpFunction());

  auto constant = fitResult.getParameterUpVariation("Constant");
  auto slope = fitResult.getParameterDownVariation("Slope");
  auto poly = fitResult.getParameterUpVariation("Poly");

  setCompositeBackgroundComponent(
      GetCompositeUpFunction(), poly, slope, constant);
}

void SingleGausFit::SetBackgroundUpFunction() {
  backgroundUpFunction->SetParameter(0, compositeUpFunction->GetParameter(3));
  backgroundUpFunction->SetParameter(1, compositeUpFunction->GetParameter(4));
  backgroundUpFunction->SetParameter(2, compositeUpFunction->GetParameter(5));
}

void SingleGausFit::SetCompositeDownComponent() {
  setCompositeSignalComponent(GetCompositeDownFunction());

  auto constant = fitResult.getParameterDownVariation("Constant");
  auto slope = fitResult.getParameterUpVariation("Slope");
  auto poly = fitResult.getParameterDownVariation("Poly");

  setCompositeBackgroundComponent(
      GetCompositeDownFunction(), poly, slope, constant);
}

void SingleGausFit::SetBackgroundDownFunction() {
  backgroundDownFunction->SetParameter(0,
                                       compositeDownFunction->GetParameter(3));
  backgroundDownFunction->SetParameter(1,
                                       compositeDownFunction->GetParameter(4));
  backgroundDownFunction->SetParameter(2,
                                       compositeDownFunction->GetParameter(5));
}

void SingleGausFit::setCompositeSignalComponent(TF1* function) {
  auto nSignalParameters = 3;
  for (auto parIdx = 0; parIdx != nSignalParameters; parIdx++) {
    setupFunctionParameter(function, parIdx);
  }
}

void SingleGausFit::setCompositeBackgroundComponent(TF1* function,
                                                    double poly,
                                                    double slope,
                                                    double constant) {
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
