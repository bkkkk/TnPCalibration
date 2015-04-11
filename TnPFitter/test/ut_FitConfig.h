#ifndef TNPFITTER_FITCONFIG_TEST_H_
#define TNPFITTER_FITCONFIG_TEST_H_ 1

#include <gtest/gtest.h>
#include "TnPFitter/FitConfig.h"

class TestFitConfig : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() { delete fit; }

  FitConfig* fit = new FitConfig{"test_composite", "test_function", "test_function", 3, 3, 1.2f, 3.4f};
};

#endif
