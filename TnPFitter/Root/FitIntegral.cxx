#include <TnPFitter/FitIntegral.h>
#include <TnPFitter/DoubleGausFit.h>
#include <TH1F.h>
#include <TF1.h>
#include <JacobUtils/LoggingUtility.h>
#include <stdexcept>

FitIntegral::
FitIntegral(const std::string& name, TH1F* histogram, double min, double max)
  : fName(name),
    fFitter(NULL)
{
  if(histogram == NULL)
  {
    LOG_ERROR() << "This histogram is empty";
    throw;
  }

  fFitter = new DoubleGausFit(name, histogram, TNPFITTER::BuildFitConfiguration(histogram));
  TNPFITTER::RunFit( fFitter );
}

//______________________________________________________________________________
FitIntegral::
FitIntegral( DoubleGausFit* fitter )
  : fName(""),
    fFitter(fitter)
{
  if(fFitter == NULL)
  {
    LOG_ERROR() << "Fitter object not constructed properly";
    throw(std::runtime_error(""));
  }

  fName = fFitter->GetName();
  TNPFITTER::RunFit( fFitter );
}

//______________________________________________________________________________
FitIntegral::
~FitIntegral()
{
  delete fFitter;
}

//______________________________________________________________________________
double FitIntegral::
GetBackgroundIntegral(int sigma)
{
  double lowLimit = fFitter->GetSigmaLow(sigma);
  double highLimit = fFitter->GetSigmaHigh(sigma);

  return(fFitter->GetBackgroundFunction()->Integral(lowLimit, highLimit));
}

//______________________________________________________________________________
double FitIntegral::
GetSignalIntegral(int sigma)
{
  TH1* histogram = fFitter->GetHistogram();

  if(histogram == NULL)
  {
    LOG_WARNING() << "Histogram not available";
    return (0);
  }

  int binMin = histogram->FindBin(fFitter->GetSigmaLow(sigma));
  int binMax = histogram->FindBin(fFitter->GetSigmaHigh(sigma));

  return( histogram->Integral(binMin, binMax) );
}

//______________________________________________________________________________
double FitIntegral::
GetCorrectedYield(int sigma)
{
  double sig = GetSignalIntegral(sigma);
  double bkg = GetBackgroundIntegral(sigma);

  return ( sig - bkg );
}

//______________________________________________________________________________
double FitIntegral::
GetBackgroundDownIntegral(int sigma)
{
  TF1* func = fFitter->GetBackgroundDownFunction();
  if(func == NULL)
  {
    throw;
  }

  double lowLimit = fFitter->GetSigmaLow(sigma);
  double highLimit = fFitter->GetSigmaHigh(sigma);

  return(func->Integral(lowLimit, highLimit));
};

//______________________________________________________________________________
double FitIntegral::
GetBackgroundUpIntegral(int sigma)
{
  TF1* func = fFitter->GetBackgroundUpFunction();
  if(func == NULL)
  {
    throw;
  }

  double lowLimit = fFitter->GetSigmaLow(sigma);
  double highLimit = fFitter->GetSigmaHigh(sigma);

  return(func->Integral(lowLimit, highLimit));
};

//______________________________________________________________________________
double FitIntegral::
GetBackgroundUncertainty (int sigma)
{
  double nominal = GetBackgroundIntegral(sigma);
  double up = fabs(GetBackgroundUpIntegral(sigma) - nominal);
  double down = fabs(GetBackgroundDownIntegral(sigma) - nominal);

  double unc = 0;

  if(up < down)
  {
    unc = down;
  }
  else
  {
    unc = up;
  }

  LOG_DEBUG1() << "Uncertainty Up: " << up << ", Uncertainty Down: " << down;
  LOG_DEBUG1() << "Uncertainty Percentage: " << unc;

  if(unc == 0)
  {
    return (0);
  }

  return(unc/nominal);
}

//______________________________________________________________________________
double FitIntegral::
GetSignalWindowUncertainty(int sigma, int window)
{
  double nominal = GetCorrectedYield(sigma);
  double wide = GetCorrectedYield(sigma + window);

  LOG_DEBUG1() << "Nominal: " << nominal << ", Wide: " << wide;
  LOG_DEBUG1() << "Uncertainty: " << fabs(wide - nominal) / nominal;

  if(fabs(wide - nominal) == 0)
  {
    return (0);
  }

  return(fabs(wide - nominal) / nominal);
}

//______________________________________________________________________________
double FitIntegral::
GetTotalUncertainty(int sigma, int window)
{
  double sig = GetSignalWindowUncertainty(sigma, window);
  double bkg = GetBackgroundUncertainty(sigma);
  double err = sqrt(sig * sig + bkg * bkg);

  return(err);
}

//______________________________________________________________________________
void FitIntegral::
Draw(int sigma, int window)
{
  if(fFitter == NULL)
  {
    throw;
  }
  
  TNPFITTER::DrawFit(fFitter, sigma, window);
}

// Streamer support
ClassImp(FitIntegral)


