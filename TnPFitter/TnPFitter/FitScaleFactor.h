#ifndef TNPFITTER_FITSCALEFACTOR_H_ 
#define TNPFITTER_FITSCALEFACTOR_H_ 1

class FitEfficiency;

#include <string>
#include "TObject.h"

class FitScaleFactor
{
public:
  // Ctor
  FitScaleFactor(const std::string& name, FitEfficiency* data, FitEfficiency* mc);

public:
  // Dtor
  ~FitScaleFactor();

public:
  double GetRecoScaleFactor(void);

public:
  double GetRecoScaleFactorError(void);

public:
  double GetSMTScaleFactor(void);

public:
  double GetSMTScaleFactorError(void);

  ClassDef(FitScaleFactor, 1)

private:
  std::string fName; // Name
  FitEfficiency* fData; // Data object
  FitEfficiency* fMC; // MC object
};

#endif
