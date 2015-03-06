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

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
