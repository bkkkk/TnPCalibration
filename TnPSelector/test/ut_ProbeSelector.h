#ifndef TJPSIPROBESELECTOR_TEST_H_
#define TJPSIPROBESELECTOR_TEST_H_ 1

#include <cpptest.h>

class TJPsiProbeSelector;

class TestProbeSelector : public Test::Suite {
private:
  TJPsiProbeSelector* selector;

public:
  TestProbeSelector() {
    TEST_ADD(TestProbeSelector::testInitialize)
    TEST_ADD(TestProbeSelector::testNumericSelection)
    TEST_ADD(TestProbeSelector::testFinalize)
  }

private:
  void testInitialize();
  void testNumericSelection();
  void testObjectSelection();
  void testFinalize();

protected:
  virtual void setup();
  virtual void tearDown();
};

#endif

#if 0
  int accept (const ITrack& track);
#endif
