#ifndef DOUBLEGAUSFIT_H_
#define DOUBLEGAUSFIT_H_ 1

#include <string>

#include <TnPFitter/IFitter.h>

class TF1;
class TH1F;

class DoubleGausFit : public IFitter {
 public:
  DoubleGausFit(std::string name, TH1F* histogram, const FitConfig& config);
  ~DoubleGausFit() = default;

 public:
  Parameters getVariationDown();
  Parameters getVariationUp();

  std::pair<double, double> GetSigmaAndMu();
  double GetSigma();
  double GetMu();
};

namespace TNPFITTER {
FitConfig BuildFitConfiguration(TH1* histogram,
                                double min = 2.63,
                                double max = 3.5);
}

#endif
