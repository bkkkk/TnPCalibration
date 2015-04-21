#include "ut_MatchResult.h"
#include "physicstools/MatchResult.h"

TEST_F(TestMatchResult, NumberConstructorShouldNotThrow) {
  EXPECT_NO_THROW(MatchResult<int>(true, 1.2, 1));
}

TEST_F(TestMatchResult, BoolOperatorReturnsCorrectValue) {
  auto matchResult = MatchResult<int>{true, 1.2, 1};
  EXPECT_TRUE(matchResult());
}

TEST_F(TestMatchResult, GetDistanceThrowsIfMatchFailed) {
  auto badResult = MatchResult<int>{false, 0.0, 0};
  EXPECT_ANY_THROW(badResult.getDistance());
}

TEST_F(TestMatchResult, GetDistanceReturnsMatchDistance) {
  auto matchResult = MatchResult<int>{true, 1.2, 0};
  EXPECT_EQ(1.2, matchResult.getDistance());
}

TEST_F(TestMatchResult, GetMatchedToReturnsMatchedIndex) {
  auto matchResult = MatchResult<int>{true, 1.2, 4};
  EXPECT_EQ(4, matchResult.getMatched());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return (RUN_ALL_TESTS());
}
