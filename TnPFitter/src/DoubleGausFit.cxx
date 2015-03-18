#include "TnPFitter/DoubleGausFit.h"

#include "JacobUtils/LoggingUtility.h"

#include <TF1.h>
#include <TH1F.h>

DoubleGausFit::DoubleGausFit(std::string name,
                             TH1F* histogram,
                             const FitConfig& configuration)
    : IFitter(name, {"DGaus"}, histogram, configuration) {
}

void DoubleGausFit::SetBackgroundFunction() {
  GetBackgroundFunction()->FixParameter(
      0, GetCompositeFunction()->GetParameter("Constant"));
  GetBackgroundFunction()->FixParameter(
      1, GetCompositeFunction()->GetParameter("Slope"));
  GetBackgroundFunction()->FixParameter(
      2, GetCompositeFunction()->GetParameter("Poly"));
}

void DoubleGausFit::SetSignalFunction() {
  GetSignalFunction()->FixParameter(
      0, GetCompositeFunction()->GetParameter("Narrow N"));
  GetSignalFunction()->FixParameter(
      1, GetCompositeFunction()->GetParameter("Narrow Mean"));
  GetSignalFunction()->FixParameter(
      2, GetCompositeFunction()->GetParameter("Narrow Sigma"));
  GetSignalFunction()->FixParameter(
      3, GetCompositeFunction()->GetParameter("Wide N"));
  GetSignalFunction()->FixParameter(
      4, GetCompositeFunction()->GetParameter("Wide Mean"));
  GetSignalFunction()->FixParameter(
      5, GetCompositeFunction()->GetParameter("Wide Sigma"));
}

void DoubleGausFit::SetCompositeUpComponent() {
  setCompositeSignalComponent(GetCompositeUpFunction());

  auto constant = fitResult.getParameterUpVariation("Constant");
  auto slope = fitResult.getParameterDownVariation("Slope");
  auto poly = fitResult.getParameterUpVariation("Poly");

  setCompositeBackgroundComponent(
      GetCompositeUpFunction(), poly, slope, constant);
}

void DoubleGausFit::SetBackgroundUpFunction() {
  GetBackgroundUpFunction()->SetParameter(
      0, GetCompositeUpFunction()->GetParameter(6));
  GetBackgroundUpFunction()->SetParameter(
      1, GetCompositeUpFunction()->GetParameter(7));
  GetBackgroundUpFunction()->SetParameter(
      2, GetCompositeUpFunction()->GetParameter(8));
}

void DoubleGausFit::SetCompositeDownComponent() {
  setCompositeSignalComponent(GetCompositeDownFunction());

  auto constant = fitResult.getParameterDownVariation("Constant");
  auto slope = fitResult.getParameterUpVariation("Slope");
  auto poly = fitResult.getParameterDownVariation("Poly");

  setCompositeBackgroundComponent(
      GetCompositeDownFunction(), poly, slope, constant);
}

void DoubleGausFit::SetBackgroundDownFunction() {
  GetBackgroundDownFunction()->SetParameter(
      0, GetCompositeDownFunction()->GetParameter(6));
  GetBackgroundDownFunction()->SetParameter(
      1, GetCompositeDownFunction()->GetParameter(7));
  GetBackgroundDownFunction()->SetParameter(
      2, GetCompositeDownFunction()->GetParameter(8));
}

void DoubleGausFit::setCompositeSignalComponent(TF1* function) {
  auto nSignalParameters = 6;
  for (auto parIndex = 0; parIndex < nSignalParameters; parIndex++) {
    setParameterFromConfig(function, parIndex);
  }
}

void DoubleGausFit::setCompositeBackgroundComponent(TF1* function,
                                                    double poly,
                                                    double slope,
                                                    double constant) {
  function->FixParameter(6, constant);
  function->FixParameter(7, slope);
  function->FixParameter(8, poly);
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
