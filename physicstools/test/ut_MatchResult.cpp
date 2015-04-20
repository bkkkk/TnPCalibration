#include "ut_MatchResult.h"
#include "physicstools/MatchResult.h"

TEST_F(TestMatchResult, NumberConstructorShouldNotThrow) {
  EXPECT_NO_THROW(MatchResult(true, 1.2));
}

TEST_F(TestMatchResult, BoolOperatorReturnsCorrectValue) {
  MatchResult matchResult = MatchResult{true, 1.2};
  EXPECT_TRUE(matchResult());
}

TEST_F(TestMatchResult, GetDistanceThrowsIfMatchFailed) {
  auto badResult = MatchResult{false, 0.0};
  EXPECT_ANY_THROW(badResult.getDistance());
}

TEST_F(TestMatchResult, GetDistanceReturnsMatchDistance) {
  auto matchResult = MatchResult{true, 1.2};
  EXPECT_EQ(1.2, matchResult.getDistance());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return (RUN_ALL_TESTS());
}
