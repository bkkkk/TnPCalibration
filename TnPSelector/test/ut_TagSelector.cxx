#include "ut_TagSelector.h"

#include <TnPSelector/TJPsiTagSelector.h>
#include "FakeMuon.h"
#include <D3PDReaderAdapter/IMuon.h>

void TestTagSelector::testInitializeWithNoParameters() {
  TJPsiTagSelector* invalidSelector = new TJPsiTagSelector;
  TEST_ASSERT(invalidSelector->initialize() == 0)
}

void TestTagSelector::testInitializeWithValidParameters() {
  TEST_ASSERT(selector->initialize() == 1)
}

void TestTagSelector::testIndividualCuts() {
  TEST_ASSERT(selector->passReconstructionCuts(5000, 2.3) == 1);
  TEST_ASSERT(selector->passIPCuts(0.2, 0.3, 1, 1) == 1);
  TEST_ASSERT(selector->passCombinedCut(true) == 1);
}

void TestTagSelector::testNumericSelectionOfBadMuon() {
  TEST_ASSERT(selector->accept(2.6, 1, 5000, 0.2, 1.4, 2.0, 2.0) == 0)
  TEST_ASSERT(selector->accept(2.4, 0, 5000, 0.2, 1.4, 2.0, 2.0) == 0)
  TEST_ASSERT(selector->accept(2.4, 1, 3000, 0.2, 1.4, 2.0, 2.0) == 0)
  TEST_ASSERT(selector->accept(2.4, 1, 5000, 0.4, 1.4, 2.0, 2.0) == 0)
  TEST_ASSERT(selector->accept(2.4, 1, 5000, 0.2, 1.6, 2.0, 2.0) == 0)
  TEST_ASSERT(selector->accept(2.4, 1, 5000, 0.2, 1.4, 4.0, 2.0) == 0)
  TEST_ASSERT(selector->accept(2.4, 1, 5000, 0.2, 1.4, 2.0, 4.0) == 0)
}

void TestTagSelector::testNumericSelectionOfGoodMuon() {
  TEST_ASSERT(selector->accept(2.4, 1, 5000, 0.2, 1.4, 0.1, 0.5) == 1)  
}

void TestTagSelector::testSelectionFromBadMuon() {
  FakeMuon badMuon; badMuon.constructBadTagMuon();
  TEST_ASSERT(selector->accept(badMuon) == 0)
}

void TestTagSelector::testSelectionFromGoodMuon() {
  FakeMuon goodMuon; goodMuon.constructGoodTagMuon();
  TEST_ASSERT(selector->accept(goodMuon) == 1)
}

void TestTagSelector::testFinalize() {
  TEST_ASSERT(selector->finalize() == 1)
}

void TestTagSelector::setup() {
  selector = new TJPsiTagSelector();
  selector->etaCut = 2.5;
  selector->combinedMuonCut = 1;
  selector->ptCut = 4000;
  selector->d0Cut = 0.3;
  selector->z0Cut = 1.5;
  selector->d0SigCut = 3.0;
  selector->z0SigCut = 3.0;
}

void TestTagSelector::tearDown() {
  delete selector;
}

int main(int argc, char const *argv[]) {
  Test::TextOutput output(Test::TextOutput::Verbose);
  TestTagSelector tku;
  return (tku.run(output) ? EXIT_SUCCESS : EXIT_FAILURE);
}
