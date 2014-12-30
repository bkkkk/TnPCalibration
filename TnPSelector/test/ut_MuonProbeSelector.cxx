#include "ut_MuonProbeSelector.h"
#include <TnPSelector/TJPsiMuonProbeSelector.h>

void TestMuonProbeSelector::testInitialize() {
  TEST_ASSERT(mp->initialize() == 0)
  mp->deltaRCut = 0.4;
  TEST_ASSERT(mp->initialize() == 1)
}

void TestMuonProbeSelector::testCheckNumericDeltaRCut() {
  mp->deltaRCut = 0.4;
  
  TEST_ASSERT(mp->accept(0.1) == 1)
  TEST_ASSERT(mp->accept(0.5) == 0)
}

void TestMuonProbeSelector::testFinalize() {
  TEST_ASSERT(1 == mp->finalize())
}

void TestMuonProbeSelector::setup() {
  mp = new TJPsiMuonProbeSelector();
}

void TestMuonProbeSelector::tearDown() {
  delete mp;
}

int main(int argc, char const *argv[]) {
  Test::TextOutput output(Test::TextOutput::Verbose);
  TestMuonProbeSelector tku;
  return (tku.run(output) ? EXIT_SUCCESS : EXIT_FAILURE);
}
