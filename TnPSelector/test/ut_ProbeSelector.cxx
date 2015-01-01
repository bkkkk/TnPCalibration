#include "ut_ProbeSelector.h"

#include <TnPSelector/TJPsiProbeSelector.h>

#include "FakeMuon.h"

void TestProbeSelector::testInitialize() {
  TJPsiProbeSelector* emptySelector = new TJPsiProbeSelector;
  TEST_ASSERT(emptySelector->initialize() == 0)

  TEST_ASSERT(selector->initialize() == 1)
}

void TestProbeSelector::testNumericSelection() {
  TEST_ASSERT(selector->accept(2.6, 4000) == 0)
  TEST_ASSERT(selector->accept(2.2, 2000) == 0)

  TEST_ASSERT(selector->accept(2.1, 4000) == 1)
}

void TestProbeSelector::testObjectSelection() {
  
}

void TestProbeSelector::testFinalize() {
  TEST_ASSERT(selector->finalize() == 1)
}

void TestProbeSelector::setup() {
  selector = new TJPsiProbeSelector;
  selector->pCut = 3000;
  selector->etaCut = 2.5;
}

void TestProbeSelector::tearDown() {
  delete selector;
}

int main(int argc, char const *argv[]) {
  Test::TextOutput output(Test::TextOutput::Verbose);
  TestProbeSelector tps;
  return (tps.run(output) ? EXIT_SUCCESS : EXIT_FAILURE);
}
