#ifndef TESTPAIRSELECTOR_H_
#define TESTPAIRSELECTOR_H_ 1

#include <gtest/gtest.h>

#include <TnPSelector/TJPsiPairSelector.h>

class TestPairSelector : public ::testing::Test {
public:
  TestPairSelector() = default;

  TJPsiPairSelector* selector;

  virtual void SetUp() {
    selector = new TJPsiPairSelector();
    selector->deltaRCutMin = 0.1;
    selector->deltaRCutMax = 1.5;
    selector->signCut = -1;
    selector->minMassCut = 1500;
    selector->maxMassCut = 4200;
    selector->deltaZ0Cut = 0.1;
  }
};

#endif
