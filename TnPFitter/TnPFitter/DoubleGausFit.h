#ifndef DOUBLEGAUSFIT_H_
#define DOUBLEGAUSFIT_H_ 1

#include <string>

#include <TnPFitter/IFitter.h>

#include <TnPFitter/FitConfig.h>
#include <TnPFitter/FitResult.h>

#include <Fit/ParameterSettings.h>

#include <TH1F.h>
#include <TF1.h>

class DoubleGausFit : public IFitter {
 public:
  DoubleGausFit(std::string val_name,
                TH1F* val_histogram,
                const FitConfig& val_fitConfig);

 public:
  ~DoubleGausFit() = default;

 public:
  void SetSignalFunction();
  void SetBackgroundFunction();
  void SetCompositeUpFunction();
  void SetCompositeUpComponent();
  void SetBackgroundUpFunction();
  void SetCompositeDownFunction();
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
// Setup a fitconfig object
FitConfig BuildFitConfiguration(TH1* histogram,
                                double min = 2.63,
                                double max = 3.5);
}

#endif
