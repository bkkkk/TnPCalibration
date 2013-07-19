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

public:  
  // Set component functions
  void setSignalFunction(void);
  void setBackgroundFunction(void);
  void setFitLimits(const double min, const double max);
  
public:
  // Integral getters
  double GetSignalIntegral(int sigma=3);
  double GetBackgroundIntegral(int sigma=3);

  TF1* GetSignalFunction(void);
  TF1* GetBackgroundFunction(void);
  TF1* GetCompositeFunction(void);

public:
  TH1F* GetHistogram(void) { return histogram; };

public:
  // Draw
  void Draw();

private:
  double GetSigmaLow(int sigma=3);
  double GetSigmaHigh(int sigma=3);

private:
  void testSignalFunction()
  {
    if(signalFunction == NULL)
    {
      LOG_ERROR() << "Signal function not set";
      setSignalFunction();
    }
  }

  void testBackgroundFunction()
  {
    if(backgroundFunction == NULL)
    {
      LOG_ERROR() << "Background function not set";
      setBackgroundFunction();
    }
  }

  void testCompositeFunction()
  {
    if(compositeFunction == NULL)
    {
      LOG_ERROR() << "Composite function not set";
      fitCompositeFunction();
    }
  }

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

namespace TNPFITTER
{
  // Setup a fitconfig object
  FitConfig BuildFitConfiguration(TH1* histogram);

  // Run fit
  int RunFit(DoubleGausFit* fitter);
}

#endif
