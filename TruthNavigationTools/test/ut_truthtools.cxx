#include <TruthNavigationTools/TruthTools.h>
#include <string>

#include "ut_TruthTools.h"

TEST_F(TestTruthTools, GetValidParticleName) {
  int electronPdgId = 11;
  std::string electronName = "e";
  EXPECT_EQ(electronName, TT::GetParticleName(electronPdgId));
  EXPECT_EQ(electronName, TT::GetParticleName(-electronPdgId));
}

TEST_F(TestTruthTools, GetNonPresentParticleName) {
  EXPECT_EQ("200", TT::GetParticleName(200));
}

TEST_F(TestTruthTools, ConvertIntToString) {
  EXPECT_EQ("1", TT::IntToString(1));
}

TEST_F(TestTruthTools, GetNameOfSibling) {
  EXPECT_EQ("Parent", GetNameOfSibling(TT::PARENT));
  EXPECT_EQ("Current", GetNameOfSibling(TT::CURRENT));
  EXPECT_EQ("Children", GetNameOfSibling(TT::CHILD));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
