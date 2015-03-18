#ifndef DOUBLEGAUSFIT_H_
#define DOUBLEGAUSFIT_H_ 1

#include <string>

#include <TnPFitter/IFitter.h>

class TF1;
class TH1F;

class DoubleGausFit : public IFitter {
 public:
  DoubleGausFit(std::string name,
                TH1F* histogram,
                const FitConfig& configuration);

 public:
  ~DoubleGausFit() = default;

 public:
  void SetSignalFunction();
  void SetBackgroundFunction();
  void SetCompositeUpComponent();
  void SetBackgroundUpFunction();
  void SetCompositeDownComponent();
  void SetBackgroundDownFunction();

 public:
  void SetCompositeErrFunction(TF1* function,
                               double poly,
                               double slope,
                               double constant);
  std::pair<double, double> GetSigmaAndMu();
  double GetSigma();
  double GetMu();

#ifdef __CINT__
  ClassDef(DoubleGausFit, 1)
#endif
};

namespace TNPFITTER {
FitConfig BuildFitConfiguration(TH1* histogram,
                                double min = 2.63,
                                double max = 3.5);
}

#endif
