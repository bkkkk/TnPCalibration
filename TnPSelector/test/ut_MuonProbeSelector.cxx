#include "ut_MuonProbeSelector.h"

TEST_F(TestMuonProbeSelector, InitializeEmpty) {
  TJPsiMuonProbeSelector empty;
  EXPECT_EQ(0, empty.initialize());
}

TEST_F(TestMuonProbeSelector, InitializeFilled) {
  EXPECT_EQ(1, mp->initialize());
}

TEST_F(TestMuonProbeSelector, Finalize) {
  EXPECT_EQ(1, mp->finalize());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
