#ifndef DOUBLEGAUSFIT_H_
#define DOUBLEGAUSFIT_H_ 1

// C++
#include <string>

// Root
#include <Fit/ParameterSettings.h>
#include <TnPFitter/FitConfig.h>
#include <TnPFitter/FitResult.h>
#include <TnPFitter/FitInterface.h>
#include <TH1F.h>
#include <TF1.h>

class DoubleGausFit : public FitInterface {
public:
  DoubleGausFit(std::string val_name,
                TH1F* val_histogram,
                const FitConfig& val_fitConfig);

public:
  ~DoubleGausFit(void);

public:  
  void SetSignalFunction();
  void SetBackgroundFunction();
  void SetCompositeUpFunction();
  void SetCompositeDownFunction();

public:
  void SetCompositeErrFunction(TF1* function, double poly, double slope, double constant);
  std::pair<double, double> GetSigmaAndMu();

#ifdef __CINT__
  ClassDef(DoubleGausFit, 1)
#endif
};

namespace TNPFITTER {
  // Setup a fitconfig object
  FitConfig BuildFitConfiguration(TH1* histogram, double min = 2.63, double max = 3.5);
}

#endif
