#include "ut_ProbeSelector.h"

#include <TnPSelector/TJPsiProbeSelector.h>

#include "FakeMuon.h"

void TestProbeSelector::testConstruct() {
}

void TestProbeSelector::setup() {
  selector = new TJPsiProbeSelector;
}

void TestProbeSelector::tearDown() {
  delete selector;
}

int main(int argc, char const *argv[]) {
  Test::TextOutput output(Test::TextOutput::Verbose);
  TestProbeSelector tku;
  return (tku.run(output) ? EXIT_SUCCESS : EXIT_FAILURE);
}
