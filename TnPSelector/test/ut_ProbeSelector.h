#ifndef TJPSIPROBESELECTOR_TEST_H_
#define TJPSIPROBESELECTOR_TEST_H_ 1

#include <cpptest.h>

class TJPsiProbeSelector;

class TestProbeSelector : public Test::Suite {
private:
  TJPsiProbeSelector* selector;

public:
  TestProbeSelector() {
    TEST_ADD(TestProbeSelector::testConstruct)
  }

private:
  void testConstruct();

protected:
  virtual void setup();
  virtual void tearDown();
};

#endif
