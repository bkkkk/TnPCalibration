#ifndef TNPFITTER_IFITTER_H_
#define TNPFITTER_IFITTER_H_ 1

#include <string>
#include <stdexcept>

#include <TF1.h>
#include <TH1F.h>

#include "TnPFitter/FitConfig.h"
#include "TnPFitter/FitResult.h"

#include "TnPFitter/FittableFunction.h"
#include "TnPFitter/CompositeFunction.h"
#include "TnPFitter/FittableGroup.h"

class IFitter {
 public:
  IFitter(std::string name,
          std::string functionName,
          TH1F* val_histogram,
          const FitConfig& val_fitConfig);

  virtual ~IFitter() { }

 public:
  TF1* GetSignalFunction();
  TF1* GetBackgroundFunction();
  TF1* GetCompositeFunction();
  TF1* GetBackgroundUpFunction();
  TF1* GetBackgroundDownFunction();
  TF1* GetCompositeUpFunction();
  TF1* GetCompositeDownFunction();

 public:
  virtual void FitCompositeFunction();
  virtual void SetCompositeUpFunction();
  virtual void SetCompositeDownFunction();

  virtual void SetSignalFunction();
  virtual void SetBackgroundFunction();

  virtual void SetCompositeUpComponent();
  virtual void SetBackgroundUpFunction();

  virtual void SetCompositeDownComponent();
  virtual void SetBackgroundDownFunction();

 protected:
  virtual Parameters getVariationDown() = 0;
  virtual Parameters getVariationUp() = 0;

 public:
  const std::string GetName() const { return name; }
  TH1F* GetHistogram() const { return histogram; }
  const FitConfig GetFitConfig() const { return fitConfig; }
  const std::string& GetFunctionName() const { return functionName; }

  virtual double GetSigmaLow(int nSigma = 3);
  virtual double GetSigmaHigh(int nSigma = 3);
  virtual std::pair<double, double> GetSigmaAndMu() = 0;
  void SetFitLimits(const double min, const double max);

 protected:
  std::string name;
  FitConfig fitConfig;
  std::string functionName;

  TH1F* histogram;
  std::string histogramName;

  double bottomFitLimit;
  double topFitLimit;

  std::size_t nSignalParameters;
  std::size_t nBackgroundParameters;

  FittableGroup fittingGroup;

  FittableFunction signal;
  FittableFunction background;

  CompositeFunction composite;
  FitResult fitResult;

  CompositeFunction compositeUp;
  FittableFunction backgroundUp;
  CompositeFunction compositeDown;
  FittableFunction backgroundDown;

#ifdef __CINT__
  ClassDef(IFitter, 1)
#endif
};

namespace TNPFITTER {
void RunFit(IFitter* fitter);
}

#endif
