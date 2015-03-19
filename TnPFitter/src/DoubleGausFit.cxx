#include "TnPFitter/DoubleGausFit.h"

#include "JacobUtils/LoggingUtility.h"

#include <TF1.h>
#include <TH1F.h>

#include "TnPFitter/FittableFunction.h"

DoubleGausFit::DoubleGausFit(std::string name,
                             TH1F* histogram,
                             const FitConfig& configuration)
    : IFitter(name, {"DGaus"}, histogram, configuration) {
  nSignalParameters = 6;
  nBackgroundParameters = 3;
}

Parameters DoubleGausFit::getVariationUp() {
  Parameters parameters = {
      {"Constant", fitResult.getParameterUpVariation("Constant")},
      {"Slope", fitResult.getParameterDownVariation("Slope")},
      {"Poly", fitResult.getParameterUpVariation("Poly")}};

  return (parameters);
}

Parameters DoubleGausFit::getVariationDown() {
  Parameters parameters = {
      {"Constant", fitResult.getParameterDownVariation("Constant")},
      {"Slope", fitResult.getParameterUpVariation("Slope")},
      {"Poly", fitResult.getParameterDownVariation("Poly")}};

  return (parameters);
}

std::pair<double, double> DoubleGausFit::GetSigmaAndMu() {
  return (std::make_pair(GetSigma(), GetMu()));
}

double DoubleGausFit::GetSigma() {
  auto sigmaNarrow = GetCompositeFunction()->GetParameter(2);
  auto sigmaWide = GetCompositeFunction()->GetParameter(5);
  return ((sigmaWide + sigmaNarrow) / 2);
}

double DoubleGausFit::GetMu() {
  auto mass = fitConfig.ParSettings(1).Value();

  auto muNarrow = GetCompositeFunction()->GetParameter(1);
  auto muWide = GetCompositeFunction()->GetParameter(4);

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
  Parameters pars = {{"Narrow N", histogram->GetMaximum(), 0, 0.0001, 10000000},
                     {"Narrow Mean", 3.097, 0, 2.8, 3.3},
                     {"Narrow Sigma", 0.1, 0, 0.02, 0.2},
                     {"Wide N", histogram->GetMaximum(), 0, 0.0001, 10000000},
                     {"Wide Mean", 3.097, 0, 2.7, 3.4},
                     {"Wide Sigma", 0.3, 0, 0.08, 0.7}};

  auto polyPlusDoubleGaus = "gaus(0) + gaus(3) + [6] + [7] * x + [8] * x * x";
  auto doubleGaus = "gaus(0) + gaus(3)";
  auto poly = "[0] + [1] * x + [2] * x * x";

  FitConfig* fitConfig = new FitConfig(polyPlusDoubleGaus, 9, min, max);

  pars.push_back({"Constant", 0});
  pars.push_back({"Slope", 0});
  pars.push_back({"Poly", 0});

  fitConfig->SetSignalFitFunction(doubleGaus);
  fitConfig->SetBackgroundFitFunction(poly);
  fitConfig->SetParamsSettings(pars);
  fitConfig->SetFitOptions("MERBQN");

  return (*fitConfig);
}

#ifdef __CINT__
ClassImp(DoubleGausFit);
#endif
