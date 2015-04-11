#ifndef TNPCALIBRATION_TESTCOMPOSITEFUNCTION_H
#define TNPCALIBRATION_TESTCOMPOSITEFUNCTION_H

#include <gtest/gtest.h>
#include <TnPFitter/FittableFunction.h>
#include <TnPFitter/TnPFitter/CompositeFunction.h>

class TestCompositeFunction : public ::testing::Test {

protected:
  TestCompositeFunction() {

  }

  virtual void SetUp() override {
    someSignal = FittableFunction{"TestSignal", signalFormula, 1.0, 2.0};
    background = FittableFunction{"", backgroundFormula, 1.0, 2.0};
    theComposite = CompositeFunction{"test_composite", composite, someSignal,
                                     background};
  }

  std::string composite = "expo(0) + [2] + [3] * x";
  std::string backgroundFormula = "[0] + [1] * x";
  std::string signalFormula = "expo(0)";
  Parameters signalParameters = {
      {"Constant", 10000, 0, 0.0001, 10000000},
      {"Slope",    3.097, 0, 2.8,    3.3}
  };
  Parameters backgroundParameters = {
      {"Bkg Constant", 10,  0, 0,   20},
      {"Bkg Slope",    0.1, 0, 0.0, 5}
  };
  FittableFunction someSignal = FittableFunction{"signal", "x", 0.0, 1.0};
  FittableFunction background = FittableFunction{"bkg", "x", 0.0, 1.0};
  CompositeFunction theComposite = CompositeFunction{"test_composite",
                                                     composite,
                                                     someSignal, background};

  void testLimitsAreTheSame(Parameter referenceParameter, TF1* theTestedFunction,
                            int index);
};


#endif
