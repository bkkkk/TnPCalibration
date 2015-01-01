#ifndef TJPSIPROBESELECTOR_TEST_H_
#define TJPSIPROBESELECTOR_TEST_H_ 1

#include <gtest/gtest.h>

#include <TnPSelector/TJPsiProbeSelector.h>

class ProbeSelectorTest : public ::testing::Test {
protected:
  ProbeSelectorTest() {
    selector = new TJPsiProbeSelector;

    selector->pCut = 3000;
    selector->etaCut = 2.5;
  }

  virtual ~ProbeSelectorTest() {
    delete selector;
  }

  TJPsiProbeSelector* selector;
};

#endif
