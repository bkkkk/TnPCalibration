#include "ut_ProbeSelector.h"

#include "FakeTrack.h"

TEST_F(ProbeSelectorTest, InitializeEmpty) {
  TJPsiProbeSelector emptySelector;
  EXPECT_EQ(0, emptySelector.initialize());
}

TEST_F(ProbeSelectorTest, InitializeFilled) {
  EXPECT_EQ(1, selector->initialize());
}

TEST_F(ProbeSelectorTest, NumericSelectGoodProbe) {
  EXPECT_EQ(1, selector->accept(2.1, 4000));
}

TEST_F(ProbeSelectorTest, NumericSelectBadProbe) {
  EXPECT_EQ(0, selector->accept(2.6, 4000));
  EXPECT_EQ(0, selector->accept(2.2, 2000));
}

TEST_F(ProbeSelectorTest, ObjectSelectGoodProbe) {
  FakeTrack goodProbe; goodProbe.constructGoodProbe();
  EXPECT_EQ(1, selector->accept(goodProbe));
}

TEST_F(ProbeSelectorTest, ObjectSelectBadProbe) {
  FakeTrack badProbe; badProbe.constructBadProbe();
  EXPECT_EQ(0, selector->accept(badProbe));
}

TEST_F(ProbeSelectorTest, FinalizeNominal) {
  EXPECT_EQ(1, selector->finalize());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
