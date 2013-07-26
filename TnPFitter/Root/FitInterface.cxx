#include "TnPFitter/FitInterface.h"
#include "TnPFitter/FitterDraw.h"

FitInterface::
FitInterface(const std::string& val_name, TH1F* val_histogram, const FitConfig& val_fitConfig)
 : name(val_name),
   fitConfig(val_fitConfig),
   functionName("NotDefined"),
   histogram(val_histogram),
   histogramName(histogram->GetName()),
   compositeFunction(NULL),
   signalFunction(NULL),
   backgroundFunction(NULL),
   compositeUpFunction(NULL),
   compositeDownFunction(NULL),
   backgroundUpFunction(NULL),
   backgroundDownFunction(NULL),
   bottomFitLimit(2.6),
   topFitLimit(3.5)
{
  fitResult = new FitResult ( name, fitConfig.NPar() );

}

//______________________________________________________________________________
FitInterface::~FitInterface()
{
  delete compositeFunction;
  delete backgroundFunction;
  delete signalFunction;
  delete backgroundUpFunction;
  delete backgroundDownFunction;
  delete compositeDownFunction;
  delete compositeUpFunction;
}

//______________________________________________________________________________
void FitInterface::
FitCompositeFunction()
{
  LOG_DEBUG() << "Fitting: " << histogram->GetName();

  compositeFunction = new TF1( functionName.c_str(), fitConfig.GetFitFunction().c_str(),
                               bottomFitLimit, topFitLimit );

  for(int parIdx = 0; parIdx != compositeFunction->GetNpar(); parIdx++)
  {
    double val = fitConfig.ParSettings(parIdx).Value();
    double min = fitConfig.ParSettings(parIdx).LowerLimit();
    double max = fitConfig.ParSettings(parIdx).UpperLimit();
    std::string namePar = fitConfig.ParSettings(parIdx).Name();

    compositeFunction->SetParName( parIdx, namePar.c_str() );
    compositeFunction->SetParameter( parIdx, val );

    if(fitConfig.ParSettings(parIdx).HasLowerLimit())
    {
      compositeFunction->SetParLimits( parIdx, min, max );
    }
  }
  
  histogram->Fit(compositeFunction, fitConfig.GetFitOptions().c_str());

  // Set Parameter results
  for(int parIdx = 0; parIdx != compositeFunction->GetNpar(); parIdx++)
  {
    std::string parName = compositeFunction->GetParName(parIdx);
    float parValue = compositeFunction->GetParameter(parIdx);
    float parError = compositeFunction->GetParError(parIdx);

    PrintVariable(parName, parValue, parError);

    fitResult->AddParameter(parName, parValue, parError);
  };

  return;
}

//______________________________________________________________________________
TF1* FitInterface::
GetBackgroundDownFunction (void)
{
  testCompositeFunction();
  return (backgroundDownFunction);
}

//______________________________________________________________________________
TF1* FitInterface::
GetBackgroundUpFunction (void)
{
  testCompositeFunction();
  return (backgroundUpFunction);
}

//______________________________________________________________________________
TF1* FitInterface::
GetCompositeFunction()
{
  testCompositeFunction();
  return (compositeFunction);
}

//______________________________________________________________________________
TF1* FitInterface::
GetSignalFunction()
{
  testSignalFunction();
  return (signalFunction);
}

//______________________________________________________________________________
TF1* FitInterface::
GetBackgroundFunction()
{
  testBackgroundFunction();
  return (backgroundFunction);
}

//______________________________________________________________________________
double FitInterface::
GetSigmaLow(int nSigma)
{
  testCompositeFunction();
  
  double sigma;
  double mu;

  GetSigmaAndMu(sigma, mu);

  double lowEdge = mu - nSigma * sigma;
  LOG_DEBUG1() << "Low edge for nSigma: " << nSigma << " is: " << lowEdge;
  
  return(lowEdge);
};

//______________________________________________________________________________
double FitInterface::
GetSigmaHigh(int nSigma)
{
  testCompositeFunction();

  double sigma;
  double mu;

  GetSigmaAndMu(sigma, mu);

  double highEdge = mu + nSigma * sigma;
  LOG_DEBUG1() << "High edge for nSigma: " << nSigma << " is: " << highEdge;

  return(highEdge);
};

//______________________________________________________________________________
void FitInterface::
SetFitLimits(const double min, const double max)
{
  bottomFitLimit = min;
  topFitLimit = max;
  return;
}

//______________________________________________________________________________
void FitInterface::
testCompositeFunction()
{
  if(compositeFunction == NULL)
  {
    LOG_ERROR() << "Composite function not set";
    FitCompositeFunction();
  }
}

//______________________________________________________________________________
void FitInterface::
testSignalFunction()
{
  if(signalFunction == NULL)
  {
    LOG_ERROR() << "Signal function not set";
    SetSignalFunction();
  }
}

//______________________________________________________________________________
void FitInterface::
testBackgroundFunction()
{
  if(backgroundFunction == NULL)
  {
    LOG_ERROR() << "Background function not set";
    SetBackgroundFunction();
  }
}

//______________________________________________________________________________
const void FitInterface::
PrintVariable(const std::string& name, double var, double err) const
{
  LOG_DEBUG1() << name << " :: Value = " << var << ", Error = " << err;
}

//______________________________________________________________________________
void TNPFITTER::
RunFit(FitInterface* fitter, int sigma, int window)
{
  if(fitter == NULL)
  {
    throw;
  }

  FitterDraw* fitterDraw = new FitterDraw(fitter, sigma, window);

  LOG_DEBUG() << "Running Fit";
  fitter->FitCompositeFunction();
  LOG_DEBUG() << "Signal Function";
  fitter->SetSignalFunction();
  LOG_DEBUG() << "Bkg Function";
  fitter->SetBackgroundFunction();
  LOG_DEBUG() << "Bkg Variation Function";
  fitter->SetCompositeDownFunction();
  fitter->SetCompositeUpFunction();
  fitterDraw->Draw();

  return;
}

//______________________________________________________________________________

ClassImp(FitInterface)
