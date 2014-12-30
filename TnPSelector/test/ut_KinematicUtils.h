#ifndef KINEMATICUTILS_TEST_H_
#define KINEMATICUTILS_TEST_H_ 1

#include <cpptest.h>

class TestKinematicUtils : public Test::Suite {
public:
  TestKinematicUtils() {
    TEST_ADD(TestKinematicUtils::testGetEta)
    TEST_ADD(TestKinematicUtils::testGetEtaThrowsOnZeroTheta)
    TEST_ADD(TestKinematicUtils::testGetPt)
    TEST_ADD(TestKinematicUtils::testGetPtThrowsOnZeroQoverp)
    TEST_ADD(TestKinematicUtils::testGetDeltaR)
    TEST_ADD(TestKinematicUtils::testGetDeltaZ0)
    TEST_ADD(TestKinematicUtils::testGetInvariantMass)
  }
  
private:
  void testGetEta();
  void testGetEtaThrowsOnZeroTheta();
  
  void testGetPt();
  void testGetPtThrowsOnZeroQoverp();

  void testGetDeltaR();
  void testGetDeltaZ0();

  void testGetInvariantMass();

private:
  std::string comparison_msg(double expected, double returned);
  void test_assert_compare(double expected, double returned);
};

#endif
