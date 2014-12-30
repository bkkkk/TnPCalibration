#include "ut_KinematicUtils.h"

#include <TnPSelector/KinematicUtils.h>

#include <math.h>

std::string TestKinematicUtils::comparison_msg(double expected, double returned) {
    std::stringstream msgStream;
    msgStream << "Expected: " << expected
              << ", Returned: " << returned;
    return msgStream.str();
}

void TestKinematicUtils::test_assert_compare(double expected, double returned) {
  TEST_ASSERT_MSG(expected == returned, comparison_msg(expected, returned).data());
}

void TestKinematicUtils::testGetEta() {
  TEST_ASSERT_DELTA(0.88, TNP::GetEta(0.785398163), 0.01)
  TEST_ASSERT_DELTA(2.44, TNP::GetEta(0.174532925), 0.01)
}

void TestKinematicUtils::testGetEtaThrowsOnZeroTheta() {
  TEST_THROWS(TNP::GetEta(0), std::logic_error)
}

void TestKinematicUtils::testGetPt() {
  test_assert_compare(0, TNP::GetPt(1, 0));
  
  test_assert_compare(1, TNP::GetPt(1, M_PI/2));
  
  test_assert_compare(0.5, TNP::GetPt(2, M_PI/2));
}

void TestKinematicUtils::testGetPtThrowsOnZeroQoverp() {
  TEST_THROWS(TNP::GetPt(0, 0), std::logic_error);  
}

void TestKinematicUtils::testGetDeltaR() {
  test_assert_compare(0, TNP::GetDeltaR(0, 0, 0, 0));

  TEST_ASSERT_DELTA(sqrt(2), TNP::GetDeltaR(1, 1, 0, 0), 0.000001);

  TEST_ASSERT_DELTA(1, TNP::GetDeltaR(1, 2 * M_PI, 0, 0), 0.000001);
}

void TestKinematicUtils::testGetDeltaZ0() {
  test_assert_compare(1, TNP::GetDeltaZ0(-3, -2));
  
  test_assert_compare(1, TNP::GetDeltaZ0(2, 3));
  test_assert_compare(1, TNP::GetDeltaZ0(3, 2));
  
  test_assert_compare(2, TNP::GetDeltaZ0(0, 2));
  
  test_assert_compare(4, TNP::GetDeltaZ0(2, -2));
  test_assert_compare(4, TNP::GetDeltaZ0(-2, 2));
}

void TestKinematicUtils::testGetInvariantMass() {
  const double MuonMass = 105.6583715;

  TEST_ASSERT_DELTA(MuonMass, TNP::GetInvariantMass(0, -2.44, 1, 0, 2.44, 2*M_PI, 0), 0.00001);
}

int main(int argc, char const *argv[]) {
  Test::TextOutput output(Test::TextOutput::Verbose);
  TestKinematicUtils tku;
  return (tku.run(output) ? EXIT_SUCCESS : EXIT_FAILURE);
}
