#include "ut_SingleGausFit.h"
#include "TnPFitter/SingleGausFit.h"
#include "TH1F.h"

TEST_F(TestSingleGausFit, ThrowWhenConstructingConfigWithEmptyHistogram) {
  EXPECT_ANY_THROW(TNPFITTER::BuildSingleGausFitConfiguration(nullptr));
}

TEST_F(TestSingleGausFit, ThrowWhenConstructingFitterWithEmptyHistogram) {
  auto empty_histogram = new TH1F("test_canvas", "test_canvas", 100, 2.0, 5.0);
  FitConfig empty_config = TNPFITTER::BuildSingleGausFitConfiguration(empty_histogram);

  EXPECT_ANY_THROW(new SingleGausFit("", nullptr, empty_config));
}

TEST_F(TestSingleGausFit, ConstructSuccessfullyWithInitializedParameters) {
  auto empty_histogram = new TH1F("test_canvas", "test_canvas", 100, 2.0, 5.0);
  FitConfig empty_config = TNPFITTER::BuildSingleGausFitConfiguration(empty_histogram);

  EXPECT_NO_THROW(new SingleGausFit("some_name", empty_histogram, empty_config));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}

/*
SingleGausFit(std::string name, TH1F* histogram, const FitConfig& fitConfig);
void SetSignalFunction();
void SetBackgroundFunction();
void SetCompositeUpFunction();
void SetCompositeDownFunction();
void SetCompositeErrFunction(TF1* function, double poly, double slope, double constant);
std::pair<double, double> GetSigmaAndMu();

TF1* GetSignalFunction();
TF1* GetBackgroundFunction();
TF1* GetCompositeFunction();
TF1* GetBackgroundUpFunction();
TF1* GetBackgroundDownFunction();
TF1* GetCompositeUpFunction();
TF1* GetCompositeDownFunction();
virtual void FitCompositeFunction();

const std::string GetName() const { return name; }
TH1F* GetHistogram() const  { return histogram; }
const FitConfig GetFitConfig() const { return fitConfig; }
const std::string& GetFunctionName() const { return functionName; }
  
virtual double GetSigmaLow (int nSigma = 3);
virtual double GetSigmaHigh (int nSigma = 3);
virtual std::pair<double, double> GetSigmaAndMu() = 0;
void SetFitLimits(const double min, const double max);

void testSignalFunction();
void testBackgroundFunction();
void testCompositeFunction();
*/

