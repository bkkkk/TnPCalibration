#include "TestCompositeFunction.h"
#include <TF1.h>

TEST_F(TestCompositeFunction,
       ConstructionWithValidFittedFunctionsDoesNotThrow) {
  EXPECT_NO_THROW(
      CompositeFunction("TestComposite", composite, someSignal, background));
}

TEST_F(TestCompositeFunction,
       ConstructionWithFunctionsWithDifferentRangesThrows) {
  FittableFunction someBackground{"", backgroundFormula, 1.2, 2.0};

  EXPECT_ANY_THROW(
      CompositeFunction("", composite, someSignal, someBackground));

  FittableFunction anotherBackground{"", backgroundFormula, 1.0, 2.1};

  EXPECT_ANY_THROW(
      CompositeFunction("", composite, someSignal, anotherBackground));
}

TEST_F(TestCompositeFunction, ConstructionSetsFormulaCorrectly) {
  auto expected = "(expo(0)+[2])+([3]*x)";
  auto returned = theComposite.getFunction()->GetExpFormula();
  EXPECT_STREQ(expected, returned);
}

TEST_F(TestCompositeFunction,
       SettingSignalParametersShouldFillCompositeFunctionCorrectly) {
  EXPECT_NO_THROW(theComposite.setSignalParameters(signalParameters));

  auto theTestedFunction = theComposite.getFunction();

  auto indexParameterToBeTested = 0ul;
  auto referenceParameter = signalParameters.at(indexParameterToBeTested);
  EXPECT_EQ(referenceParameter.Value(),
            theTestedFunction->GetParameter(indexParameterToBeTested));

  testLimitsAreTheSame(referenceParameter, theTestedFunction, indexParameterToBeTested);
}

TEST_F(TestCompositeFunction,
       SettingBackgroundParametersShouldFillCompositeFunctionCorrectly) {
  EXPECT_NO_THROW(theComposite.setBackgroundParameters(backgroundParameters));

  auto theTestedFunction = theComposite.getFunction();
  ASSERT_EQ(4, theTestedFunction->GetNpar());

  auto indexParameterToBeTested = 0ul;
  auto referenceParameter = backgroundParameters.at(indexParameterToBeTested);

  auto indexOffsetDueToSignal = 2ul;
  auto offsetedIndex = (indexParameterToBeTested + indexOffsetDueToSignal);

  EXPECT_EQ(referenceParameter.Value(),
            theTestedFunction->GetParameter(offsetedIndex));
  testLimitsAreTheSame(referenceParameter, theTestedFunction, offsetedIndex);
}

void TestCompositeFunction::testLimitsAreTheSame(Parameter referenceParameter, TF1* theTestedFunction, int index) {
  double xmin = 0;
  double xmax = 0;
  theTestedFunction->GetParLimits(index, xmin, xmax);
  EXPECT_EQ(referenceParameter.LowerLimit(), xmin);
  EXPECT_EQ(referenceParameter.UpperLimit(), xmax);
}

int main(int argc, char** args) {
  ::testing::InitGoogleTest(&argc, args);
  return (RUN_ALL_TESTS());
}

