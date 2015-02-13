#ifndef TNPFITTER_FITEFFICIENCY_H_
#define TNPFITTER_FITEFFICIENCY_H_ 1

#include <string>
#include <math.h>

class DoubleGausFit;
class FitIntegral;
class TH1F;

class FitEfficiency {
public:
  FitEfficiency(std::string name,
                TH1F* probeHisto, TH1F* muonProbeHisto, TH1F* smtHisto,
                double min = 2.61, double max = 3.5);  
  FitEfficiency(std::string name,
                FitIntegral* probeIntegral,
                FitIntegral* muonProbeIntegral,
                FitIntegral* smtIntegral);
  ~FitEfficiency();

public:
  void Draw(void);

  double GetSMTError(int nSigma = 3, int windowSize = 2);
  double GetSMTEfficiency(int nSigma = 3);
  double GetRecoError(int nSigma = 3, int windowSize = 2);
  double GetRecoEfficiency(int nSigma = 3);

public:
  std::string fName;
  FitIntegral* fProbeIntegral;
  FitIntegral* fMuonProbeIntegral;
  FitIntegral* fSmtIntegral;

#ifdef __CINT__
  ClassDef(FitEfficiency, 1)
#endif
};

namespace TNPFITTER {
  double GetEfficiency(FitIntegral* top, FitIntegral* bottom, int nSigma = 3);
  inline constexpr double GetEfficiency(double top, double bottom) {
    return(top/bottom);
  }
  
  double GetTotalUncertainty(FitIntegral* top, FitIntegral* bottom, int nSigma = 3, int windowSize = 2);

  inline double GetTotalUncertainty(double top, double bottom) {
    return(sqrt(top * top + bottom * bottom));
  }
}

#endif
