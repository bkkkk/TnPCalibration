#include "TnPFitter/FitScaleFactor.h"
#include "TnPFitter/FitEfficiency.h"

//_____________________________________________________________________________
FitScaleFactor::
FitScaleFactor(const std::string& name, FitEfficiency* data, FitEfficiency* mc)
  : fName(name),
    fData(data),
    fMC(mc)
{

};

//_____________________________________________________________________________
FitScaleFactor::
~FitScaleFactor()
{

};

//_____________________________________________________________________________
double FitScaleFactor::
GetRecoScaleFactor(void)
{
  double recoEffData = fData->GetRecoEfficiency();
  double recoEffMC = fMC->GetRecoEfficiency();

  return(recoEffData/recoEffMC);
};

//_____________________________________________________________________________
double FitScaleFactor::
GetRecoScaleFactorError(void)
{
  return(0.);
};

//_____________________________________________________________________________
double FitScaleFactor::
GetSMTScaleFactor(void)
{
  double smtEffData = fData->GetSMTEfficiency();
  double smtEffMC = fMC->GetSMTEfficiency();

  return(smtEffData / smtEffMC);
};

//_____________________________________________________________________________
double FitScaleFactor::
GetSMTScaleFactorError(void)
{
  return(0.);
};

ClassImp(FitScaleFactor)
