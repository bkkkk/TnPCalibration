#include "ut_TagSelector.h"

#include "FakeMuon.h"

TEST_F(TestTagSelector, InitializeWithNoParameters) {
  TJPsiTagSelector* invalidSelector = new TJPsiTagSelector;
  EXPECT_EQ(0, invalidSelector->initialize());
}

TEST_F(TestTagSelector, InitializeWithValidParameters) {
  EXPECT_EQ(1, selector->initialize());
}

TEST_F(TestTagSelector, testIndividualCuts) {
  EXPECT_EQ(1, selector->passReconstructionCuts(5000, 2.3));
  EXPECT_EQ(1, selector->passIPCuts(0.2, 0.3, 1, 1));
  EXPECT_EQ(1, selector->passCombinedCut(true));
}

TEST_F(TestTagSelector, NumericSelectionOfBadMuon) {
  EXPECT_EQ(0, selector->accept(2.6, 1, 5000, 0.2, 1.4, 2.0, 2.0));
  EXPECT_EQ(0, selector->accept(2.4, 0, 5000, 0.2, 1.4, 2.0, 2.0));
  EXPECT_EQ(0, selector->accept(2.4, 1, 3000, 0.2, 1.4, 2.0, 2.0));
  EXPECT_EQ(0, selector->accept(2.4, 1, 5000, 0.4, 1.4, 2.0, 2.0));
  EXPECT_EQ(0, selector->accept(2.4, 1, 5000, 0.2, 1.6, 2.0, 2.0));
  EXPECT_EQ(0, selector->accept(2.4, 1, 5000, 0.2, 1.4, 4.0, 2.0));
  EXPECT_EQ(0, selector->accept(2.4, 1, 5000, 0.2, 1.4, 2.0, 4.0));
}

TEST_F(TestTagSelector, NumericSelectionOfGoodMuon) {
  EXPECT_EQ(1, selector->accept(2.4, 1, 5000, 0.2, 1.4, 2.0, 2.0));
}

TEST_F(TestTagSelector, SelectionOfBadMuon) {
  auto badMuon = FakeMuon::ConstructBadTagMuon();
  EXPECT_EQ(0, selector->accept(badMuon));
}

TEST_F(TestTagSelector, SelectionOfGoodMuon) {
  auto goodMuon = FakeMuon::ConstructGoodTagMuon();
  EXPECT_EQ(1, selector->accept(goodMuon));
}

TEST_F(TestTagSelector, Finalize) {
  EXPECT_EQ(1, selector->finalize());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
