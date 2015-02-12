#ifndef TNPCLASSIFIER_TEST_H_
#define TNPCLASSIFIER_TEST_H_ 1

#include <gtest/gtest.h>
#include <TnPSelector/>

class ut_TnPClassifier : public ::testing::Test {
protected:
  virtual void SetUp() {
    selector = new TJPsiClassifier();
  }

  virtual void TearDown() {
    delete selector;
  }

  TJPsiClassifier* selector;
};

#endif