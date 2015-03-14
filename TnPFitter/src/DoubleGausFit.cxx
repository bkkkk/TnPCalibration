#include "TnPFitter/DoubleGausFit.h"
#include "TnPFitter/FitDrawingHelpers.h"

#include "JacobUtils/LoggingUtility.h"

#include "TCanvas.h"
#include "TLine.h"

#ifdef __CINT__
ClassImp(DoubleGausFit);
#endif

DoubleGausFit::DoubleGausFit(std::string val_name,
                             TH1F* val_histogram,
                             const FitConfig& val_fitConfig)
    : IFitter(val_name, {"DGaus"}, val_histogram, val_fitConfig) {
}

DoubleGausFit::~DoubleGausFit() {
}

void DoubleGausFit::SetBackgroundFunction() {
  testCompositeFunction();

  auto funcName = functionName + "_" + histogramName;

  backgroundFunction = new TF1(funcName.c_str(),
                               fitConfig.GetBackgroundFitFunction().c_str(),
                               bottomFitLimit,
                               topFitLimit);

  backgroundFunction->FixParameter(0,
                                   compositeFunction->GetParameter("Constant"));
  backgroundFunction->FixParameter(1, compositeFunction->GetParameter("Slope"));
  backgroundFunction->FixParameter(2, compositeFunction->GetParameter("Poly"));
  backgroundFunction->SetLineColor(6);
  backgroundFunction->SetLineStyle(7);
}

void DoubleGausFit::SetSignalFunction() {
  testCompositeFunction();

  auto funcName = functionName + "_signal_" + histogramName;

  signalFunction = new TF1(funcName.c_str(),
                           fitConfig.GetSignalFitFunction().c_str(),
                           bottomFitLimit,
                           topFitLimit);

  signalFunction->FixParameter(0, compositeFunction->GetParameter("Narrow N"));
  signalFunction->FixParameter(1,
                               compositeFunction->GetParameter("Narrow Mean"));
  signalFunction->FixParameter(2,
                               compositeFunction->GetParameter("Narrow Sigma"));
  signalFunction->FixParameter(3, compositeFunction->GetParameter("Wide N"));
  signalFunction->FixParameter(4, compositeFunction->GetParameter("Wide Mean"));
  signalFunction->FixParameter(5,
                               compositeFunction->GetParameter("Wide Sigma"));

  signalFunction->SetLineColor(kRed);
}

//______________________________________________________________________________
void DoubleGausFit::SetCompositeUpFunction(void) {
  testCompositeFunction();

  auto funcNameComp = functionName + "_Composite_Up_" + histogramName;
  auto funcNameBkg = functionName + "_Bkg_Up_" + histogramName;

  backgroundUpFunction = new TF1(funcNameBkg.c_str(),
                                 fitConfig.GetBackgroundFitFunction().c_str(),
                                 bottomFitLimit,
                                 topFitLimit);

  compositeUpFunction = new TF1(funcNameComp.c_str(),
                                fitConfig.GetFitFunction().c_str(),
                                bottomFitLimit,
                                topFitLimit);

  auto constant =
      fitResult.GetParValue("Constant") + fitResult.GetParError("Constant");
  auto slope = fitResult.GetParValue("Slope") - fitResult.GetParError("Slope");
  auto poly = fitResult.GetParValue("Poly") + fitResult.GetParError("Poly");

  SetCompositeErrFunction(compositeUpFunction, poly, slope, constant);

  histogram->Fit(compositeUpFunction, fitConfig.GetFitOptions().c_str());

  backgroundUpFunction->SetParameter(0, compositeUpFunction->GetParameter(6));
  backgroundUpFunction->SetParameter(1, compositeUpFunction->GetParameter(7));
  backgroundUpFunction->SetParameter(2, compositeUpFunction->GetParameter(8));
}

void DoubleGausFit::SetCompositeDownFunction() {
  testCompositeFunction();

  auto funcNameComp = functionName + "_Composite_Down_" + histogramName;
  auto funcNameBkg = functionName + "_Bkg_Down_" + histogramName;

  backgroundDownFunction = new TF1(funcNameBkg.c_str(),
                                   fitConfig.GetBackgroundFitFunction().c_str(),
                                   bottomFitLimit,
                                   topFitLimit);

  compositeDownFunction = new TF1(funcNameComp.c_str(),
                                  fitConfig.GetFitFunction().c_str(),
                                  bottomFitLimit,
                                  topFitLimit);

  auto constant =
      fitResult.GetParValue("Constant") - fitResult.GetParError("Constant");
  auto slope = fitResult.GetParValue("Slope") + fitResult.GetParError("Slope");
  auto poly = fitResult.GetParValue("Poly") - fitResult.GetParError("Poly");

  SetCompositeErrFunction(compositeDownFunction, poly, slope, constant);

  histogram->Fit(compositeDownFunction, fitConfig.GetFitOptions().c_str());

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
  auto muNarrow = compositeFunction->GetParameter(1);
  auto sigmaNarrow = compositeFunction->GetParameter(2);

  auto muWide = compositeFunction->GetParameter(4);
  auto sigmaWide = compositeFunction->GetParameter(5);

  auto sigma = (sigmaWide + sigmaNarrow) / 2;
  auto mu = 0.0;

  auto mass = fitConfig.ParSettings(1).Value();
  auto diffMuNarrow = fabs(mass - muNarrow);
  auto diffMuWide = fabs(mass - muWide);

  if (diffMuWide < diffMuNarrow) {
    mu = muWide;
  } else {
    mu = muNarrow;
  }

  auto pair = std::make_pair(sigma, mu);

  return (pair);
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
