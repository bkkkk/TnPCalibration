#ifndef HYBRIDGAUSFIT_H_
#define HYBRIDGAUSFIT_H_ 1

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

class HybridGausFit : public FitInterface
{
public:
  HybridGausFit(const std::string& name, TH1F* histogram,
                const FitConfig& fitConfig);

public:
  // Dtor
  ~HybridGausFit(void);

public:
  // Set component functions
  void SetCompositeFunction (void);
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
  FitConfig BuildHybridGausFitConfiguration(TH1* histogram);
}

#endif
