#include "TnPFitter/FitScaleFactor.h"
#include "TnPFitter/FitEfficiency.h"

FitScaleFactor::FitScaleFactor(const std::string& name, FitEfficiency* data, FitEfficiency* mc)
  : fName(name),
    fData(data),
    fMC(mc) { }

FitScaleFactor::~FitScaleFactor() { }

double FitScaleFactor::GetRecoScaleFactor() {
  auto recoEffData = fData->GetRecoEfficiency();
  auto recoEffMC = fMC->GetRecoEfficiency();

  auto sf = recoEffData/recoEffMC;

  return(sf);
}

double FitScaleFactor::GetRecoScaleFactorError() {
  return(0.f);
}

double FitScaleFactor::GetSMTScaleFactor() {
  auto smtEffData = fData->GetSMTEfficiency();
  auto smtEffMC = fMC->GetSMTEfficiency();

  auto sf = smtEffData / smtEffMC;

  return(sf);
}

double FitScaleFactor::GetSMTScaleFactorError(void) {
  return(0.);
}

#ifdef __CINT__
ClassImp(FitScaleFactor)
#endif
