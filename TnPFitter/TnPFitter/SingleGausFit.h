#ifndef SINGLEGAUSFIT_H_
#define SINGLEGAUSFIT_H_ 1

// Package includes
#include <TnPFitter/FitConfig.h>
#include <TnPFitter/FitResult.h>
#include <TnPFitter/FitInterface.h>

// Root includes
#include <Fit/ParameterSettings.h>

// STL includes
#include <string>

// Forward declares
class TF1;
class TH1F;

class SingleGausFit : public FitInterface
{
public:
  SingleGausFit(const std::string& name, TH1F* histogram,
                const FitConfig& fitConfig);

public:
  // Dtor
  ~SingleGausFit(void);

public:
  // Set component functions
  void SetSignalFunction (void);
  void SetBackgroundFunction (void);
  void SetCompositeUpFunction (void);
  void SetCompositeDownFunction (void);

public:
  void SetCompositeErrFunction(TF1* function, double poly, double slope, double constant);
  void GetSigmaAndMu(double& sigma, double& mu); 
};

namespace TNPFITTER
{
  // Setup fit config object
  FitConfig BuildSingleGausFitConfiguration(TH1* histogram);
}

#endif
