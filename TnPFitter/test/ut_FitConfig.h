#ifndef TNPFITTER_FITCONFIG_TEST_H_
#define TNPFITTER_FITCONFIG_TEST_H_ 1

#include <gtest/gtest.h>
#include "TnPFitter/FitConfig.h"

class TestFitConfig : public ::testing::Test {
protected:
  TestFitConfig() { }

  virtual void SetUp() {
    fit = new FitConfig("test_function", 6, true, 1.2f, 3.4f);
  }

  virtual void TearDown() {
    delete fit;
  }

  FitConfig* fit;
};

#endif
