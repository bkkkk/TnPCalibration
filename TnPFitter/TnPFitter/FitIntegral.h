#ifndef TNPFITTER_FITINTEGRAL_H_
#define TNPFITTER_FITINTEGRAL_H_ 1

#include <string>

#include "TnPFitter/SingleGausFit.h"

class TH1F;

class FitIntegral {
 public:
  FitIntegral(IFitter* fitter);
  FitIntegral(std::string name,
              TH1F* histogram,
              double min = 2.63,
              double max = 3.5);

 public:
  ~FitIntegral();

 public:
  double GetSignalIntegral(int sigma = 3);
  double GetBackgroundIntegral(int sigma = 3);
  double GetCorrectedYield(int sigma = 3);
  double GetBackgroundDownIntegral(int sigma = 3);
  double GetBackgroundUpIntegral(int sigma = 3);
  double GetBackgroundUncertainty(int sigma = 3);
  double GetSignalWindowUncertainty(int sigma = 3, int window = 2);
  double GetTotalUncertainty(int sigma = 3, int window = 2);
  void Draw(int sigma = 3, int window = 2);

 private:
  std::string fName;
  IFitter* fFitter;

#ifdef __CINT__
  ClassDef(FitIntegral, 1)
#endif
};

#endif