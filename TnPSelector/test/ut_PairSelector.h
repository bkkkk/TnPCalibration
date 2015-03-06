#ifndef TESTPAIRSELECTOR_H_
#define TESTPAIRSELECTOR_H_ 1

#include <gtest/gtest.h>

#include <TnPSelector/TJPsiPairSelector.h>

class TestPairSelector : public ::testing::Test {
public:
  TestPairSelector() = default;

  virtual void SetUp() {
    TJPsiPairSelector* selector = new TJPsiPairSelector();
    selector->deltaRCutMax = 0.1;
    selector->deltaRCutMin = 1.5;
    selector->signCut = -1;
    selector->minMassCut = 1.5;
    selector->maxMassCut = 4.2;
    selector->deltaZ0Cut = 0.1;
  }
};

#endif
