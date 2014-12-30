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
  }
  
private:
  void testGetEta();
  void testGetEtaThrowsOnZeroTheta();
  
  void testGetPt();
  void testGetPtThrowsOnZeroQoverp();

  void testGetDeltaR();
  void testGetDeltaZ0();

private:
  std::string comparison_msg(double expected, double returned);
  void test_assert_compare(double expected, double returned);
};

#endif

/*
  TVector3 GetTrack3Vector (const float pt, const float eta, const float phi);
  
  TLorentzVector GetTrackVector(const float pt, const float eta, const float phi);

  TLorentzVector GetMuonVector(const float pt, const float eta, const float phi, const float E);

  TVector3 GetMuon3Vector(const float pt, const float eta, const float phi);

  float GetInvariantMass(const float trackpt, const float tracketa, const float trackphi,
                         const float tagpt, const float tageta, const float tagphi, const float tagE);
*/