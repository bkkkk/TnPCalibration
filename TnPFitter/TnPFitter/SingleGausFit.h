#ifndef SINGLEGAUSFIT_H_
#define SINGLEGAUSFIT_H_ 1

#include <TnPFitter/IFitter.h>

#include <string>

class TF1;
class TH1F;

class SingleGausFit : public IFitter {
 public:
  SingleGausFit(std::string name, TH1F* histogram, const FitConfig& fitConfig);
  virtual ~SingleGausFit() = default;

 public:
  void SetSignalFunction();
  void SetBackgroundFunction();
  void SetCompositeUpFunction();
  double getParameterUpVariation(const std::string& name);
  double getParamterDownVariation(const std::string& name);
  void SetCompositeDownFunction();

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
