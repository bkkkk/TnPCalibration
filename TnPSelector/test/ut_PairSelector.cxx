#include "ut_PairSelector.h"
#include "TnPSelector/TJPsiPairSelector.h"

#include "FakeTracks.h"
#include "FakeTrack.h"
#include "FakeMuons.h"
#include "FakeMuon.h"

TEST_F(TestPairSelector, TestInitializeFailsForEmptySelector) {
  TJPsiPairSelector* emptySelector = new TJPsiPairSelector();
  EXPECT_EQ(0, emptySelector->initialize());
}

TEST_F(TestPairSelector, TestInitializePassForFilledSelector) {
  EXPECT_EQ(1, selector->initialize());
}

TEST_F(TestPairSelector, TestGoodPairPassesNumericInvariantMassCheck) {
  EXPECT_EQ(true, selector->isInInvariantMassRange(3.14));
}

/*
TEST_F(TestPairSelector, TestGoodPairPassesNumericAccept) {
  EXPECT_EQ(1, selector->accept(0.5, -1, 3.14, 0.05));
}
*/

/*
int accept(const IMuon& tag, const IMuon& muonProbe);
int accept(const IMuon& tag, const ITrack& probe);
int accept(float deltaR, float sign, float invMass, float deltaZ0);
*/

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
