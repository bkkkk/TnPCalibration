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


class DoubleGausFit : public FitInterface 
{
public:
  DoubleGausFit(const std::string& val_name="", TH1F* val_histogram=NULL, const FitConfig& val_fitConfig = FitConfig("", 0, false) );

public:
  // dtor
  ~DoubleGausFit(void);

public:  
  // Set component functions
  void SetSignalFunction (void);
  void SetBackgroundFunction (void);
  void SetCompositeUpFunction (void);
  void SetCompositeDownFunction (void);

public:
  void SetCompositeErrFunction(TF1* function, double poly, double slope, double constant);
  void GetSigmaAndMu(double& sigma, double& mu);

  ClassDef(DoubleGausFit, 1)
};

namespace TNPFITTER
{
  // Setup a fitconfig object
  FitConfig BuildFitConfiguration(TH1* histogram);

  // Run fit
  int RunFit(DoubleGausFit* fitter, int sigma, int window);
}

#endif
