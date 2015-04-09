#ifndef SINGLEGAUSFIT_H_
#define SINGLEGAUSFIT_H_ 1

#include <string>

#include <TnPFitter/IFitter.h>

class SingleGausFit : public IFitter {
 public:
  SingleGausFit(std::string name, TH1F* histogram, const FitConfig& config);
  ~SingleGausFit() = default;

  Parameters getVariationDown();
  Parameters getVariationUp();

  std::pair<double, double> GetSigmaAndMu();
};

namespace TNPFITTER {
FitConfig BuildSingleGausFitConfiguration(TH1* histogram,
                                          double min = 2.63,
                                          double max = 3.5);
}

#endif
