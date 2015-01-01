#include "ut_KinematicUtils.h"

#include <TnPSelector/KinematicUtils.h>

#include <math.h>

#include <gtest/gtest.h>

TEST(GetEta, Positive) {
  EXPECT_NEAR(0.88, TNP::GetEta(0.785398163), 0.01);
  EXPECT_NEAR(2.44, TNP::GetEta(0.174532925), 0.01);
}

TEST(GetPt, Positive) {  
  EXPECT_EQ(1, TNP::GetPt(1, M_PI/2));
  
  EXPECT_EQ(0.5, TNP::GetPt(2, M_PI/2));
}

TEST(GetPt, ZeroTheta) {
  EXPECT_EQ(0, TNP::GetPt(1, 0));  
}

TEST(GetDeltaR, AllZero) {
  EXPECT_EQ(0, TNP::GetDeltaR(0, 0, 0, 0));
}

TEST(GetDeltaR, Positive) {
  EXPECT_FLOAT_EQ(sqrt(2), TNP::GetDeltaR(1, 1, 0, 0));
  EXPECT_FLOAT_EQ(1, TNP::GetDeltaR(1, 2 * M_PI, 0, 0));
}

TEST(GetEta, ThrowsOnZeroTheta) {
  EXPECT_THROW(TNP::GetEta(0), std::logic_error);
}

TEST(GetPt, ThrowsOnZeroQoverp) {
  EXPECT_THROW(TNP::GetPt(0, 0), std::logic_error);  
}

TEST(GetDeltaZ0Test, Zero) {
  EXPECT_EQ(2, TNP::GetDeltaZ0(0, 2));
}

TEST(GetDeltaZ0Test, AllNegative) {
  EXPECT_EQ(1, TNP::GetDeltaZ0(-3, -2));
}

TEST(GetDeltaZ0Test, AllPositive) {
  EXPECT_EQ(1, TNP::GetDeltaZ0(2, 3));
  EXPECT_EQ(1, TNP::GetDeltaZ0(3, 2));
}

TEST(GetDeltaZ0Test, MixedSign) {
  EXPECT_EQ(4, TNP::GetDeltaZ0(2, -2));
  EXPECT_EQ(4, TNP::GetDeltaZ0(-2, 2));
}

TEST(GetInvariantMass, Nominal) {
  const double MuonMass = 105.6583715;

  EXPECT_FLOAT_EQ(MuonMass, TNP::GetInvariantMass(0, -2.44, 1, 0, 2.44, 2*M_PI, 0));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
