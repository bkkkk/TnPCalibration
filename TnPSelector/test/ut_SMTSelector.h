#ifndef TJPSISMTSELECTOR_TEST_H_
#define TJPSISMTSELECTOR_TEST_H_ 1

#include <gtest/gtest.h>

#include <TnPSelector/TJPsiSMTSelector.h>

class TestSMTSelector : public ::testing::Test {
protected:
  TJPsiSMTSelector* smtSelector;

  TestSMTSelector() {
  }

  virtual void SetUp() {
    smtSelector = new TJPsiSMTSelector;
    smtSelector->d0Cut = 3.0;
    smtSelector->z0SinCut = 3.0;
    smtSelector->chi2Cut = 3.2;
  }

  virtual void TearDown() {
    delete smtSelector;
  }
};

#endif
