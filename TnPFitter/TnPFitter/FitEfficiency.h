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
  FitEfficiency( const std::string& name,
                 TH1F* probeHisto,
                 TH1F* muonProbeHisto,
                 TH1F* smtHisto,
                 double min = 2.61,
                 double max = 3.5 );
  
public:
  ~FitEfficiency();

public:
  // Draws all the fitted plots
  void Draw(void);

public:
  double GetSMTError(int nSigma = 3, int windowSize = 2);
  double GetSMTEfficiency(int nSigma = 3);

public:
  double GetRecoError(int nSigma = 3, int windowSize = 2);
  double GetRecoEfficiency(int nSigma = 3);

  ClassDef(FitEfficiency, 1)
};

namespace TNPFITTER 
{
  // Returns efficiency based on two FitIntegral objects
  double GetEfficiency(FitIntegral* top, FitIntegral* bottom, int nSigma = 3);

  // Returns efficiency based on two yields
  double GetEfficiency(double top, double bottom);

  // Returns the total uncertainty based on two FitIntegral objects
  double GetTotalUncertainty(FitIntegral* top, FitIntegral* bottom, int nSigma = 3, int windowSize = 2);

  // Retrusn the total uncertainty based on two uncertainties
  double GetTotalUncertainty(double top, double bottom);
}

#endif
