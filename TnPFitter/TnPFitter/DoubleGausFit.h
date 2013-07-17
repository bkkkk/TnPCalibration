#ifndef DOUBLEGAUSFIT_H_
#define DOUBLEGAUSFIT_H_ 1

// C++
#include <string>

// Root
#include <Fit/ParameterSettings.h>
#include <TnPFitter/FitConfig.h>
#include <TnPFitter/FitResult.h>
#include <TH1F.h>
#include <TF1.h>


class DoubleGausFit
{
public:
  DoubleGausFit(const std::string& val_name="", TH1F* val_histogram=NULL, const FitConfig& val_fitConfig = FitConfig("", 0, false) );

public:
  // dtor
  ~DoubleGausFit(void);

public:
  // fitCompositeFunction
  void fitCompositeFunction();
  
  // Set component functions
  void setSignalFunction(void);
  void setBackgroundFunction(void);
  void setFitLimits(const double min, const double max)
  {
    bottomFitLimit = min;
    topFitLimit = max;
  };

public:
  TH1F* GetHistogram(void) { return histogram; };

public:
  // Draw
  void Draw();

private:
  // Name
  std::string name;
  FitConfig fitConfig;

  // Input histograms
  TH1F* histogram;
  TF1* compositeFunction;
  TF1* signalFunction;
  TF1* backgroundFunction;
  bool fLowMode;

  // Fit Limits
  double bottomFitLimit;
  double topFitLimit;

  // Fit Results
  FitResult* fitResult;
};

#endif

namespace TNPFITTER
{
  // Setup a fitconfig object
  FitConfig BuildFitConfiguration(TH1* histogram);

  // Run fit
  int RunFit(DoubleGausFit* fitter);
}
