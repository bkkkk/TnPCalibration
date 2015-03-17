#include "TnPFitter/DoubleGausFit.h"

#include "JacobUtils/LoggingUtility.h"

#include <TF1.h>
#include <TH1F.h>

DoubleGausFit::DoubleGausFit(std::string val_name,
                             TH1F* val_histogram,
                             const FitConfig& val_fitConfig)
    : IFitter(val_name, {"DGaus"}, val_histogram, val_fitConfig) {
}

void DoubleGausFit::SetBackgroundFunction() {
  backgroundFunction->FixParameter(0,
                                   compositeFunction->GetParameter("Constant"));
  backgroundFunction->FixParameter(1, compositeFunction->GetParameter("Slope"));
  backgroundFunction->FixParameter(2, compositeFunction->GetParameter("Poly"));
}

void DoubleGausFit::SetSignalFunction() {
  signalFunction->FixParameter(0, compositeFunction->GetParameter("Narrow N"));
  signalFunction->FixParameter(1,
                               compositeFunction->GetParameter("Narrow Mean"));
  signalFunction->FixParameter(2,
                               compositeFunction->GetParameter("Narrow Sigma"));
  signalFunction->FixParameter(3, compositeFunction->GetParameter("Wide N"));
  signalFunction->FixParameter(4, compositeFunction->GetParameter("Wide Mean"));
  signalFunction->FixParameter(5,
                               compositeFunction->GetParameter("Wide Sigma"));
}

void DoubleGausFit::SetCompositeUpFunction() {
  testCompositeFunction();
  SetCompositeUpComponent();

  histogram->Fit(compositeUpFunction, fitConfig.GetFitOptions().c_str());
  SetBackgroundUpFunction();
}

void DoubleGausFit::SetCompositeUpComponent() {
  auto constant = fitResult.getParameterUpVariation("Constant");
  auto slope = fitResult.getParameterDownVariation("Slope");
  auto poly = fitResult.getParameterUpVariation("Poly");

  SetCompositeErrFunction(compositeUpFunction, poly, slope, constant);
}

void DoubleGausFit::SetBackgroundUpFunction() {
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
  auto constant = fitResult.getParameterDownVariation("Constant");
  auto slope = fitResult.getParameterUpVariation("Slope");
  auto poly = fitResult.getParameterDownVariation("Poly");

  SetCompositeErrFunction(compositeDownFunction, poly, slope, constant);
}

void DoubleGausFit::SetBackgroundDownFunction() {
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
