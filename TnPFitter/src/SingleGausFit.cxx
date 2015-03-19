#include "TnPFitter/SingleGausFit.h"

#include "JacobUtils/LoggingUtility.h"

#include <TF1.h>
#include <TH1F.h>

SingleGausFit::SingleGausFit(std::string name,
                             TH1F* histogram,
                             const FitConfig& fitConfig)
    : IFitter(name, {"SGaus"}, histogram, fitConfig) {
  nSignalParameters = 3;
  nBackgroundParameters = 3;
}

Parameters SingleGausFit::getVariationUp() {
  Parameters parameters = {
      {"Constant", fitResult.getParameterUpVariation("Constant")},
      {"Slope", fitResult.getParameterDownVariation("Slope")},
      {"Poly", fitResult.getParameterUpVariation("Poly")}};

  return (parameters);
}

Parameters SingleGausFit::getVariationDown() {
  Parameters parameters = {
      {"Constant", fitResult.getParameterDownVariation("Constant")},
      {"Slope", fitResult.getParameterUpVariation("Slope")},
      {"Poly", fitResult.getParameterDownVariation("Poly")}};

  return (parameters);
}


std::pair<double, double> SingleGausFit::GetSigmaAndMu() {
  auto mu = GetCompositeFunction()->GetParameter(1);
  auto sigma = GetCompositeFunction()->GetParameter(2);

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
