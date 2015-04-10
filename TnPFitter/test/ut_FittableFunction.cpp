#include "ut_FittableFunction.h"
#include "TnPFitter/FittableFunction.h"

TEST_F(TestFittableFunction, ConstructingWithValidParametersDoesNotThrow) {
    EXPECT_NO_THROW(FittableFunction("test", "gaus(0)", 1.0, 3.0));
}

TEST_F(TestFittableFunction, ConstructingWithInvertedRangeThrowsException) {
    EXPECT_ANY_THROW(FittableFunction("test", "gaus(0)", 3.0, 1.0));
}

TEST_F(TestFittableFunction, GetParametersShouldReturnCorrectNumberOfParameters) {
    EXPECT_EQ(2ul, function->getParameters().size());
}

TEST_F(TestFittableFunction, SettingDifferentNumberOfParametersToFunctionThrowsException) {
    FittableFunction tooFewParameters{"test", "[1] * x", 1.0, 3.0};
    FittableFunction tooManyParameters{"test", "[0] + [1] * x + [2] * x * x", 1.0, 3.0};

    EXPECT_ANY_THROW(tooManyParameters.setupParametersFromConfig(pars));
}

TEST_F(TestFittableFunction, SettingUpParametersSetsParametersCorrectly) {
    function->setupParametersFromConfig(pars);

    EXPECT_EQ(2ul, function->getParameters().size());

    auto returned = function->getParameters().at(0);
    auto expected = pars.at(0);

    EXPECT_STREQ(expected.Name().c_str(), returned.Name().c_str());
    EXPECT_EQ(expected.Value(), returned.Value());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return (RUN_ALL_TESTS());
}

