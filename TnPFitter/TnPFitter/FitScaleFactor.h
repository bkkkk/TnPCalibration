#pragma once

#include <string>
#include "TObject.h"

class FitEfficiency;

class FitScaleFactor {
 public:
  FitScaleFactor(const std::string& name,
                 FitEfficiency* data,
                 FitEfficiency* mc);
  ~FitScaleFactor();

  double GetRecoScaleFactor();
  double GetRecoScaleFactorError();
  double GetSMTScaleFactor();
  double GetSMTScaleFactorError();

 private:
  std::string fName;
  FitEfficiency* fData;
  FitEfficiency* fMC;

#ifdef __CINT__
  ClassDef(FitScaleFactor, 1)
#endif
};
