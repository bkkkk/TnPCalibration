#ifndef TNPFITTER_FITEFFICIENCY_H_
#define TNPFITTER_FITEFFICIENCY_H_ 1

#include <string>
#include "TObject.h"

class DoubleGausFit;
class FitIntegral;
class TH1F;

class FitEfficiency
{
public:
  // Integration objects
  std::string fName;
  FitIntegral* fProbeIntegral;
  FitIntegral* fMuonProbeIntegral;
  FitIntegral* fSmtIntegral;

public:
  FitEfficiency(const std::string& name, TH1F* probeHisto, TH1F* muonProbeHisto, TH1F* smtHisto);
  
public:
  ~FitEfficiency();

public:
  double GetSMTError(void);
  double GetSMTEfficiency(void);

public:
  double GetRecoError(void);
  double GetRecoEfficiency(void);

  ClassDef(FitEfficiency, 1)
};

namespace TNPFITTER 
{
  // Returns efficiency based on two FitIntegral objects
  double GetEfficiency(FitIntegral* top, FitIntegral* bottom);

  // Returns efficiency based on two yields
  double GetEfficiency(double top, double bottom);

  // Returns the total uncertainty based on two FitIntegral objects
  double GetTotalUncertainty(FitIntegral* top, FitIntegral* bottom);

  // Retrusn the total uncertainty based on two uncertainties
  double GetTotalUncertainty(double top, double bottom);
}

#endif
