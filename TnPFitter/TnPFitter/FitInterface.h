#ifndef TNPFITTER_FITINTERFACE_H_
#define TNPFITTER_FITINTERFACE_H_ 1

//
#include <string>
#include <stdexcept>

// Root
#include <TF1.h>
#include <TH1F.h>

//
#include "TnPFitter/FitConfig.h"
#include "TnPFitter/FitResult.h"

class FitInterface
{
public:
  FitInterface(const std::string& name,
               TH1F* val_histogram,
               const FitConfig& val_fitConfig);
  
  virtual ~FitInterface(void);

public:
  TF1* GetSignalFunction (void);
  TF1* GetBackgroundFunction (void);
  TF1* GetCompositeFunction (void);
  TF1* GetBackgroundUpFunction (void);
  TF1* GetBackgroundDownFunction (void);
  TF1* GetCompositeUpFunction (void);
  TF1* GetCompositeDownFunction (void);

public:  
  // Set component functions
  virtual void FitCompositeFunction(void);
  virtual void SetSignalFunction (void) = 0;
  virtual void SetBackgroundFunction (void) = 0;
  virtual void SetCompositeUpFunction (void) = 0;
  virtual void SetCompositeDownFunction (void) = 0;

public:
  // Get Name
  const std::string GetName(void) const { return name; }
  std::string GetName(void) { return name; }

public:
  // Get Histogram
  TH1F* GetHistogram (void) { return histogram; }
  const TH1F* GetHistogram (void) const  { return histogram; }
  
public:
  // Helper functions
  virtual double GetSigmaLow (int nSigma = 3);
  virtual double GetSigmaHigh (int nSigma = 3);
  virtual void GetSigmaAndMu(double& sigma, double& mu) = 0;
  void SetFitLimits(const double min, const double max);

public:
  // Get Fit Configuration
  const FitConfig GetFitConfig() const { return fitConfig; }
  FitConfig GetFitConfig() { return fitConfig; }

public:
  // Get Function Name
  const std::string& GetFunctionName() const { return functionName; }
  std::string& GetFunctionName() { return functionName; }

protected:
  const void PrintVariable(const std::string& name, double var, double err) const;

protected:
  // Test functions
  void testSignalFunction();
  void testBackgroundFunction();
  void testCompositeFunction();

protected:    
  // Name
  std::string name;
  FitConfig fitConfig;
  std::string functionName;

  // Input histogram
  TH1F* histogram;
  std::string histogramName;
  
  // Nominal functions
  TF1* compositeFunction;
  TF1* signalFunction;
  TF1* backgroundFunction;
  
  // Variation histograms
  TF1* compositeUpFunction;
  TF1* compositeDownFunction;
  TF1* backgroundUpFunction;
  TF1* backgroundDownFunction;

  // Fit Limits
  double bottomFitLimit;
  double topFitLimit;

  // Fit Results
  FitResult* fitResult;

  ClassDef(FitInterface, 1)

};

namespace TNPFITTER
{
  void RunFit(FitInterface* fitter);
  void DrawFit(FitInterface* fitter, int sigma, int window);
  bool IsHighBackground(TH1* histogram, double fittingEdge, double threshold = 0.07);
}

#endif
