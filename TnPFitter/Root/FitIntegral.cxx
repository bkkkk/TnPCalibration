#include <TnPFitter/FitIntegral.h>
#include <TnPFitter/DoubleGausFit.h>
#include <TnPFitter/SingleGausFit.h>
#include <TH1F.h>
#include <TF1.h>
#include <JacobUtils/LoggingUtility.h>
#include <stdexcept>

FitIntegral::FitIntegral(const std::string& name, TH1F* histogram, double min, double max)
  : fName(name),
    fFitter(nullptr) {
  
  if(histogram == nullptr) {
    throw(std::runtime_error("This histogram is empty"));
  }

  auto threshold = 0.07;

  if(TNPFITTER::IsLowBackground(histogram, min, threshold)) {
    fFitter = new DoubleGausFit(fName, histogram, TNPFITTER::BuildFitConfiguration(histogram, min, max));
  } else {
    fFitter = new SingleGausFit(fName, histogram, TNPFITTER::BuildSingleGausFitConfiguration(histogram, min, max));
  }

  TNPFITTER::RunFit(fFitter);
}

FitIntegral::FitIntegral(FitInterface* fitter)
  : fName(""),
    fFitter(fitter) {
  if(fFitter == nullptr) {
    throw(std::runtime_error(""));
  }

  fName = fFitter->GetName();
  TNPFITTER::RunFit(fFitter);
}

FitIntegral::~FitIntegral() {
  delete fFitter;
}

double FitIntegral::GetBackgroundIntegral(int sigma) {
  auto lowLimit = fFitter->GetSigmaLow(sigma);
  auto highLimit = fFitter->GetSigmaHigh(sigma);
  auto integral = fFitter->GetBackgroundFunction()->Integral(lowLimit, highLimit);

  return(integral);
}

double FitIntegral::GetSignalIntegral(int sigma) {
  auto histogram = fFitter->GetHistogram();

  if(histogram == nullptr) {
    return (0.0);
  }

  auto binMin = histogram->FindBin(fFitter->GetSigmaLow(sigma));
  auto binMax = histogram->FindBin(fFitter->GetSigmaHigh(sigma));

  return(histogram->Integral(binMin, binMax));
}

double FitIntegral::GetCorrectedYield(int sigma) {
  auto sig = GetSignalIntegral(sigma);
  auto bkg = GetBackgroundIntegral(sigma);

  auto corrected_yield = sig - bkg;

  return (corrected_yield);
}

double FitIntegral::GetBackgroundDownIntegral(int sigma) {
  auto function = fFitter->GetBackgroundDownFunction();
  if(function == nullptr) {
    throw(std::runtime_error("Background down function is empty"));
  }

  auto low_limit = fFitter->GetSigmaLow(sigma);
  auto high_limit = fFitter->GetSigmaHigh(sigma);
  auto integral = function->Integral(low_limit, high_limit);

  return(integral);
}

double FitIntegral::GetBackgroundUpIntegral(int sigma) {
  auto function = fFitter->GetBackgroundUpFunction();
  
  if(function == nullptr) {
    throw(std::runtime_error("Background down function is empty"));
  }

  auto low_limit = fFitter->GetSigmaLow(sigma);
  auto high_limit = fFitter->GetSigmaHigh(sigma);
  auto integral = function->Integral(low_limit, high_limit);

  return(integral);
}

double FitIntegral::GetBackgroundUncertainty (int sigma) {
  auto nominal = GetBackgroundIntegral(sigma);
  auto up = fabs(GetBackgroundUpIntegral(sigma) - nominal);
  auto down = fabs(GetBackgroundDownIntegral(sigma) - nominal);

  auto uncertainty = std::max(up, down);

  return((uncertainty == 0) ? 0 : uncertainty/nominal);
}

double FitIntegral::GetSignalWindowUncertainty(int sigma, int window) {
  auto nominal = GetCorrectedYield(sigma);
  auto wide = GetCorrectedYield(sigma + window);

  auto difference = fabs(wide - nominal);

  auto relative_difference = difference / nominal;
  
  return(relative_difference);
}

double FitIntegral::GetTotalUncertainty(int sigma, int window) {
  auto sig = GetSignalWindowUncertainty(sigma, window);
  auto bkg = GetBackgroundUncertainty(sigma);
  auto err = sqrt(sig * sig + bkg * bkg);

  return(err);
}

void FitIntegral::Draw(int sigma, int window) {
  if(fFitter == nullptr) {
    throw(std::runtime_error("Fitter improperly set"));
  }
  
  TNPFITTER::DrawFit(fFitter, sigma, window);
}

#ifdef __CINT__
ClassImp(FitIntegral)
#endif


