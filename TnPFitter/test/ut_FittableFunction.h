#ifndef TNPCALIBRATION_UT_FITTABLEFUNCTION_H
#define TNPCALIBRATION_UT_FITTABLEFUNCTION_H

#include <gtest/gtest.h>
#include <TnPFitter/TnPFitter/FitConfig.h>
#include <TnPFitter/TnPFitter/FittableFunction.h>

class TestFittableFunction : public ::testing::Test {
protected:
    virtual void SetUp() override;

    virtual void TearDown() override;

    Parameters pars;
    FittableFunction* function;
};

#endif

void TestFittableFunction::SetUp() {
    function = new FittableFunction{"test", "[0] + [1] * x", 1.0, 3.0};
    pars = {{"Intersect", 1, 0, 0, 10},  {"Slope", 3, 0, 1, 5}};
}

void TestFittableFunction::TearDown() {

}
