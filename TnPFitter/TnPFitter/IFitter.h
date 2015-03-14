#ifndef TNPFITTER_IFITTER_H_
#define TNPFITTER_IFITTER_H_ 1

#include <string>
#include <stdexcept>

#include <TF1.h>
#include <TH1F.h>

#include "TnPFitter/FitConfig.h"
#include "TnPFitter/FitResult.h"

class IFitter {
 public:
  IFitter(std::string name,
          std::string functionName,
          TH1F* val_histogram,
          const FitConfig& val_fitConfig);
  IFitter(std::string name,
          TH1F* val_histogram,
          const FitConfig& val_fitConfig);

  virtual ~IFitter();

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
  virtual void SetSignalFunction() = 0;
  virtual void SetBackgroundFunction() = 0;
  virtual void SetCompositeUpFunction() = 0;
  virtual void SetCompositeDownFunction() = 0;

 private:
  void setupMainCompositeFunction();

 protected:
  void setupFunctionParameter(TF1* function, std::size_t index);

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
  void PrintVariable(const std::string& name, double var, double err) const;

 protected:
  void testSignalFunction();
  void testBackgroundFunction();
  void testCompositeFunction();

  std::string name;
  FitConfig fitConfig;
  std::string functionName;

  TH1F* histogram;
  std::string histogramName;

  TF1* compositeFunction;
  TF1* signalFunction;
  TF1* backgroundFunction;

  TF1* compositeUpFunction;
  TF1* compositeDownFunction;
  TF1* backgroundUpFunction;
  TF1* backgroundDownFunction;

  double bottomFitLimit;
  double topFitLimit;

  FitResult fitResult;

#ifdef __CINT__
  ClassDef(IFitter, 1)
#endif
};

namespace TNPFITTER {
void RunFit(IFitter* fitter);
}

#endif
