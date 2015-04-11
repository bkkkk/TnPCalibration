#include "TnPFitter/DoubleGausFit.h"

#include "JacobUtils/LoggingUtility.h"

#include <TF1.h>
#include <TH1F.h>

#include "TnPFitter/FittableFunction.h"
#include "TnPFitter/CompositeFunction.h"
#include "TnPFitter/FittableGroup.h"

DoubleGausFit::DoubleGausFit(std::string name,
                             TH1F *histogram,
                             const FitConfig &configuration)
        : IFitter(name, {"DGaus"}, histogram, configuration) {
    nSignalParameters = 6;
    nBackgroundParameters = 3;
}

Parameters DoubleGausFit::getVariationUp() {
    Parameters parameters = {
            {"Constant", fitResult.getParameterUpVariation("Constant")},
            {"Slope",    fitResult.getParameterDownVariation("Slope")},
            {"Poly",     fitResult.getParameterUpVariation("Poly")}};

    return (parameters);
}

Parameters DoubleGausFit::getVariationDown() {
    Parameters parameters = {
            {"Constant", fitResult.getParameterDownVariation("Constant")},
            {"Slope",    fitResult.getParameterUpVariation("Slope")},
            {"Poly",     fitResult.getParameterDownVariation("Poly")}};

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
    const auto Mass = fitConfig.getSignalParameter(1).Value();

    auto muNarrow = GetCompositeFunction()->GetParameter(1);
    auto muWide = GetCompositeFunction()->GetParameter(4);

    auto diffMuNarrow = fabs(Mass - muNarrow);
    auto diffMuWide = fabs(Mass - muWide);

    auto mu = 0.0f;

    if (diffMuWide < diffMuNarrow) {
        mu = muWide;
    } else {
        mu = muNarrow;
    }

    return (mu);
}

FitConfig TNPFITTER::BuildFitConfiguration(TH1 *histogram,
                                           double min,
                                           double max) {
    auto doubleGaus = "gaus(0) + gaus(3)";
    auto poly = "[0] + [1] * x + [2] * x * x";
    auto composite = "gaus(0) + gaus(3) + [6] + [7] * x + [8] * x * x";

    FitConfig *fitConfig = new FitConfig(composite, doubleGaus, poly, 6, 3, min, max);
    Parameters signalParameters = {
            {"Narrow N",     histogram->GetMaximum(), 0, 0.0001, 10000000},
            {"Narrow Mean",  3.097,                   0, 2.8,    3.3},
            {"Narrow Sigma", 0.1,                     0, 0.02,   0.2},
            {"Wide N",       histogram->GetMaximum(), 0, 0.0001, 10000000},
            {"Wide Mean",    3.097,                   0, 2.7,    3.4},
            {"Wide Sigma",   0.3,                     0, 0.08,   0.7}};
    fitConfig->setSignalParameters(signalParameters);

    Parameters bkgParameters = {{"Constant", 0},
                                {"Slope",    0},
                                {"Poly",     0}};
    fitConfig->setBkgParameters(bkgParameters);
    fitConfig->SetFitOptions("MERBQN");

    return (*fitConfig);
}

#ifdef __CINT__
ClassImp(DoubleGausFit);
#endif
