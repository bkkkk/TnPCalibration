#ifndef TJPSIMUONPROBESELECTOR_TEST_H_
#define TJPSIMUONPROBESELECTOR_TEST_H_ 1

#include <gtest/gtest.h>

#include <TnPSelector/TJPsiMuonProbeSelector.h>

class TestMuonProbeSelector : public ::testing::Test {
protected:
  TJPsiMuonProbeSelector* mp;

  TestMuonProbeSelector() {
  }

  virtual void SetUp() {
    mp = new TJPsiMuonProbeSelector;
    mp->deltaRCut = 0.4;
  }

  virtual void TearDown() {
    delete mp;
  }
};

#endif
