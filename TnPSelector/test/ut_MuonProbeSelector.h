#ifndef TJPSIMUONPROBESELECTOR_TEST_H_
#define TJPSIMUONPROBESELECTOR_TEST_H_ 1

#include <cpptest.h>

class TJPsiMuonProbeSelector;

class TestMuonProbeSelector : public Test::Suite {
private:
  TJPsiMuonProbeSelector* mp;

public:
  TestMuonProbeSelector() {
    TEST_ADD(TestMuonProbeSelector::testInitialize)
    TEST_ADD(TestMuonProbeSelector::testCheckNumericDeltaRCut)
    TEST_ADD(TestMuonProbeSelector::testFinalize)
  }

private:
  void testInitialize();
  void testCheckNumericDeltaRCut();
  void testFinalize();

protected:
  virtual void setup();
  virtual void tearDown();
};

#endif

/*
int accept(const ITrack& probe, const IMuons& muons, int& muonProbeIdx);
*/
