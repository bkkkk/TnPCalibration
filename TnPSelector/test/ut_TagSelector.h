#ifndef TJPSITAGSELECTOR_TEST_H_
#define TJPSITAGSELECTOR_TEST_H_ 1

#include <gtest/gtest.h>
#include <TnPSelector/TJPsiTagSelector.h>

class TestTagSelector : public ::testing::Test {
protected:
  TestTagSelector() {
  }

  virtual void SetUp() {
    selector = new TJPsiTagSelector();
    selector->etaCut = 2.5;
    selector->combinedMuonCut = 1;
    selector->ptCut = 4000;
    selector->d0Cut = 0.3;
    selector->z0Cut = 1.5;
    selector->d0SigCut = 3.0;
    selector->z0SigCut = 3.0;
  }

  virtual void TearDown() {
    delete selector;
  }

  TJPsiTagSelector* selector;
};

#endif
