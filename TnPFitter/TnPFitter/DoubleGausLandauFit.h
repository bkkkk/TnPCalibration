#ifndef TNPFITTER_DOUBLEGAUSLANDAUFIT_H_
#define TNPFITTER_DOUBLEGAUSLANDAUFIT_H_ 1

#include "TnPFitter/FitInterface.h"

/**
 * class DoubleGausLandauFit
 *    Implementation of FitInterface for a landau/gaussian signal and poly background
 */
class DoubleGausLandauFit : public FitInterface
{
public:
  // Ctir
  DoubleGausLandauFit(const std::string& val_name = "",
                      TH1F* val_histogram=NULL,
                      const FitConfig& val_fitConfig = FitConfig("", 0, false));

public:
  // Dtor
  ~DoubleGausLandauFit();

public:
  // Sets all the additional functions for display purposes
  // and background uncertainty estimation
  void SetSignalFunction (void);
  void SetBackgroundFunction (void);
  void SetCompositeUpFunction (void);
  void SetCompositeDownFunction (void);

public:
  // Convenience function to set up the composite functions for error estimation  
  void SetCompositeErrFunction(TF1* function, double poly, double slope, double constant);

public:
  // Returns the selected sigma and mu
  void GetSigmaAndMu(double& sigma, double& mu);

  ClassDef(DoubleGausLandauFit, 1)
};

namespace LANDAUFIT
{
  // Constructs the fitting configuration
  FitConfig BuildFitConfiguration(TH1* histogram);
}

#endif