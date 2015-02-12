#include "ut_SMTSelector.h"

#include "FakeMuon.h"

TEST_F(TestSMTSelector, InitializeEmpty) {
  TJPsiSMTSelector empty;
  EXPECT_EQ(0, empty.initialize());
}

TEST_F(TestSMTSelector, InitializeFilled) {
  EXPECT_EQ(1, smtSelector->initialize());
}

TEST_F(TestSMTSelector, NumericSelectionOfBadProbe) {
  EXPECT_EQ(0, smtSelector->accept(4.0, 0.05, 3.2));
  EXPECT_EQ(0, smtSelector->accept(0.3, 4.0, 3.2));
  EXPECT_EQ(0, smtSelector->accept(0.3, 0.05, 4));
}

TEST_F(TestSMTSelector, NumericSelectionOfGoodProbe) {
  EXPECT_EQ(1, smtSelector->accept(0.3, 0.05, 0.3));
  EXPECT_EQ(1, smtSelector->accept(-0.3, -0.05, 0.3));
}

TEST_F(TestSMTSelector, ObjectSelectGoodSMT) {
  auto goodSMT = FakeMuon::ConstructGoodTagMuon();
  EXPECT_EQ(1, smtSelector->accept(goodSMT));
}

TEST_F(TestSMTSelector, ObjectSelectBadSMT) {
  auto badSMT = FakeMuon::ConstructBadTagMuon();
  EXPECT_EQ(0, smtSelector->accept(badSMT));
}

TEST_F(TestSMTSelector, Finalize) {
  EXPECT_EQ(1, smtSelector->finalize());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
