#pragma once

#include <gtest/gtest.h>
#include "TnPFitter/FitConfig.h"

class SingleGausFit;

class TestSingleGausFit : public ::testing::Test {
 protected:
  virtual void SetUp() {}

  virtual void TearDown() {}

  SingleGausFit* fitter;
};
