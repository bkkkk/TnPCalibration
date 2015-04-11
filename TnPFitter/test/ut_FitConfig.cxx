#include "ut_FitConfig.h"
#include "TnPFitter/FitConfig.h"

TEST_F(TestFitConfig, InitializeWithEmptyFunction) {
  EXPECT_ANY_THROW(FitConfig("", "sig_func", "bkg_func", 3, 3, 2.4f, 4.5f));
  EXPECT_ANY_THROW(FitConfig("func", "", "bkg_func", 3, 3, 2.4f, 4.5f));
  EXPECT_ANY_THROW(FitConfig("func", "sig_func", "", 3, 3, 2.4f, 4.5f));
  EXPECT_ANY_THROW(FitConfig("", "sig_func", "bkg_func", 3, 3, 2.4f, 4.5f));
  EXPECT_ANY_THROW(FitConfig("func", "sig_func", "bkg_func", 0, 3, 2.4f, 4.5f));
  EXPECT_ANY_THROW(FitConfig("func", "sig_func", "bkg_func", 3, 0, 2.4f, 4.5f));
  EXPECT_ANY_THROW(FitConfig("func", "sig_func", "bkg_func", 3, 3, 4.5f, 3.5f));
  EXPECT_ANY_THROW(FitConfig("func", "sig_func", "bkg_func", 3, 3, 4.5f, 4.5f));
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

TEST_F(TestFitConfig, SetInvalidBkgFunction) {
  EXPECT_ANY_THROW(fit->SetBackgroundFitFunction(""));
}

TEST_F(TestFitConfig, GetValidBkgFunction) {
  EXPECT_EQ("test_function", fit->GetBackgroundFitFunction());
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
  EXPECT_EQ("test_function", fit->GetSignalFitFunction());
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
