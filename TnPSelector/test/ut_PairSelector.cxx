#include "ut_PairSelector.h"
#include "TnPSelector/TJPsiPairSelector.h"

#include "./FakeTracks.h"
#include "./FakeTrack.h"
#include "./FakeMuons.h"
#include "./FakeMuon.h"

TEST_F(TestPairSelector, TestInitializeFailsForEmptySelector) {
  TJPsiPairSelector* emptySelector = new TJPsiPairSelector();
  EXPECT_EQ(0, emptySelector->initialize());
}

TEST_F(TestPairSelector, TestInitializeFailsForBadlySetupDeltaRCuts) {
  selector->deltaRCutMax = 0.1;
  selector->deltaRCutMin = 1.5;
  EXPECT_EQ(0, selector->initialize());
}

TEST_F(TestPairSelector, TestInitializeFailsForBadInvariantMassRange) {
  selector->minMassCut = 0.4;
  selector->maxMassCut = 0.1;
  EXPECT_EQ(0, selector->initialize());
}

TEST_F(TestPairSelector, TestInitializeFailsForBadDeltaZCut) {
  selector->deltaZ0Cut = 0.0;
  EXPECT_EQ(0, selector->initialize());
}

TEST_F(TestPairSelector, TestInitializePassForFilledSelector) {
  EXPECT_EQ(1, selector->initialize());
}

TEST_F(TestPairSelector, TestGoodPairPassesNumericInvariantMassCheck) {
  EXPECT_EQ(true, selector->isInInvariantMassRange(3140));
}

TEST_F(TestPairSelector, TestGoodPairPassesDeltaRCheck) {
  EXPECT_EQ(true, selector->isInDeltaRRange(1.0));
}

TEST_F(TestPairSelector, TestGoodPairPassesNumericAccept) {
  EXPECT_EQ(1, selector->accept(0.5, -1, 3140, 0.05));
}

TEST_F(TestPairSelector, TestBadPairFailsNumericAccept) {
  EXPECT_EQ(0, selector->accept(100.0, -1, 3140, 0.05));
}

TEST_F(TestPairSelector, TestGoodProbePairPassesAccept) {
  EXPECT_EQ(1, selector->accept(FakeMuon::ConstructGoodTagMuon(),
                                FakeTrack::ConstructGoodProbe()));
}

TEST_F(TestPairSelector, TestBadProbePairFailsAccept) {
  EXPECT_EQ(0, selector->accept(FakeMuon::ConstructGoodTagMuon(),
                                FakeTrack::ConstructBadProbe()));
}

/*
int accept(const IMuon& tag, const IMuon& muonProbe);
int accept(const IMuon& tag, const ITrack& probe);
*/

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
