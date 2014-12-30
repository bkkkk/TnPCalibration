#ifndef KINEMATICUTILS_TEST_H_
#define KINEMATICUTILS_TEST_H_ 1

#include <cpptest.h>

class TestKinematicUtils : public Test::Suite {
public:
  TestKinematicUtils() {
    TEST_ADD(TestKinematicUtils::testGetEtaFromZero)
  }
  ~TestKinematicUtils() {}
  
private:
  void testGetEtaFromZero();

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

  float GetPt(const float qoverp, const float theta);

  float GetDeltaZ0(const float first, const float second);

  float GetDeltaR(const float firstEta, const float firstPhi, const float secondEta, const float secondPhi );
*/