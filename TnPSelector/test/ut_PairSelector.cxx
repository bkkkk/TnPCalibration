#include "ut_PairSelector.h"
#include "TnPSelector/TJPsiPairSelector.h"

#include "FakeTracks.h"
#include "FakeTrack.h"
#include "FakeMuons.h"
#include "FakeMuon.h"

TEST_F(TestPairSelector, TestInitializeFailsForEmptySelector) {
  TJPsiPairSelector* selector = new TJPsiPairSelector();
  EXPECT_EQ(0, selector->initialize());
}

TEST_F(TestPairSelector, TestInitializePassForFilledSelector) {
  TJPsiPairSelector* selector = new TJPsiPairSelector();
  selector->deltaRCutMax = 0.1;
  selector->deltaRCutMin = 1.5;
  selector->signCut = -1;
  selector->minMassCut = 1.5;
  selector->maxMassCut = 4.2;
  selector->deltaZ0Cut = 0.1;
  EXPECT_EQ(1, selector->initialize());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
