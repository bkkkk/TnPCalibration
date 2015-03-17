#ifndef SINGLEGAUSFIT_H_
#define SINGLEGAUSFIT_H_ 1

#include <string>

#include <TnPFitter/IFitter.h>

class TF1;
class TH1F;

class SingleGausFit : public IFitter {
 public:
  SingleGausFit(std::string name, TH1F* histogram, const FitConfig& fitConfig);
  virtual ~SingleGausFit() = default;

 public:
  void SetSignalFunction();
  void SetBackgroundFunction();
  void SetCompositeUpComponent();
  void SetBackgroundUpFunction();
  void SetCompositeDownComponent();
  void SetBackgroundDownFunction();

  void SetCompositeErrFunction(TF1* function,
                               double poly,
                               double slope,
                               double constant);
  std::pair<double, double> GetSigmaAndMu();
};

namespace TNPFITTER {
FitConfig BuildSingleGausFitConfiguration(TH1* histogram,
                                          double min = 2.63,
                                          double max = 3.5);
}

#endif
