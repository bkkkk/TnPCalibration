#include "ut_FitConfig.h"
#include "TnPFitter/FitConfig.h"

TEST_F(TestFitConfig, InitializeWithEmptyFunction) {
  EXPECT_ANY_THROW(new FitConfig("", 6, 2.4f, 4.5f));
  EXPECT_ANY_THROW(new FitConfig("some_function", 0, 2.4f, 4.5f));
  EXPECT_ANY_THROW(new FitConfig("some_function", 6, 4.5f, 3.5f));
  EXPECT_ANY_THROW(new FitConfig("some_function", 6, 4.5f, 4.5f));
}

TEST_F(TestFitConfig, GetValidLimits) {
  EXPECT_EQ(1.2f, fit->GetFitMin());
  EXPECT_EQ(3.4f, fit->GetFitMax());
}

TEST_F(TestFitConfig, SetInvalidFitLimits) {
  EXPECT_ANY_THROW(fit->SetFitLimits(2.5f, 2.5f));
  EXPECT_ANY_THROW(fit->SetFitLimits(4.5f, 2.5f));
}

TEST_F(TestFitConfig, SetValidFitLimits) {
  auto min = 2.5f;
  auto max = 4.5f;
  EXPECT_NO_THROW(fit->SetFitLimits(min, max));

  EXPECT_EQ(min, fit->GetFitMin());
  EXPECT_EQ(max, fit->GetFitMax());
}

TEST_F(TestFitConfig, SetInvalidFunction) {
  EXPECT_ANY_THROW(fit->SetFitFunction(""));
}

TEST_F(TestFitConfig, GetValidFunction) {
  EXPECT_STREQ("test_function", fit->GetFitFunction().c_str());
}

TEST_F(TestFitConfig, SetValidFunction) {
  auto newFunction = "a_new_function";
  EXPECT_NO_THROW(fit->SetFitFunction(newFunction));
  EXPECT_STREQ(newFunction, fit->GetFitFunction().c_str());
}

TEST_F(TestFitConfig, SetInvalidBkgFunction) {
  EXPECT_ANY_THROW(fit->SetBackgroundFitFunction(""));
}

TEST_F(TestFitConfig, GetValidBkgFunction) {
  EXPECT_EQ("", fit->GetBackgroundFitFunction());
}

TEST_F(TestFitConfig, SetValidBkgFunction) {
  auto newFunction = "a_new_function";
  EXPECT_NO_THROW(fit->SetBackgroundFitFunction(newFunction));
  EXPECT_EQ(newFunction, fit->GetBackgroundFitFunction());
}

TEST_F(TestFitConfig, SetInvalidSigFunction) {
  EXPECT_ANY_THROW(fit->SetSignalFitFunction(""));
}

TEST_F(TestFitConfig, GetValidSigFunction) {
  EXPECT_EQ("", fit->GetSignalFitFunction());
}

TEST_F(TestFitConfig, SetValidSigFunction) {
  auto newFunction = "a_new_function";
  EXPECT_NO_THROW(fit->SetSignalFitFunction(newFunction));
  EXPECT_EQ(newFunction, fit->GetSignalFitFunction());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
