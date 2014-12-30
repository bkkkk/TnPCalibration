#include "ut_KinematicUtils.h"
#include "../TnPSelector/KinematicUtils.h"

std::string TestKinematicUtils::comparison_msg(double expected, double returned) {
    std::stringstream msgStream;
    msgStream << "Expected: " << expected
              << ", Returned: " << returned;
    return msgStream.str();
}

void TestKinematicUtils::test_assert_compare(double expected, double returned) {
  TEST_ASSERT_MSG(expected == returned, comparison_msg(expected, returned).data());
}

void TestKinematicUtils::testGetEtaFromZero() {
  TEST_ASSERT_DELTA(0.88, TNP::GetEta(0.785398163), 0.01);
  TEST_ASSERT_DELTA(2.44, TNP::GetEta(0.174532925), 0.01);
}

int main(int argc, char const *argv[]) {
  Test::TextOutput output(Test::TextOutput::Verbose);
  TestKinematicUtils tku;
  return (tku.run(output) ? EXIT_SUCCESS : EXIT_FAILURE);
}

/*
  TVector3 GetTrack3Vector (const float pt, const float eta, const float phi);
  
  TLorentzVector GetTrackVector(const float pt, const float eta, const float phi);

  TLorentzVector GetMuonVector(const float pt, const float eta, const float phi, const float E);

  TVector3 GetMuon3Vector(const float pt, const float eta, const float phi);

  float GetInvariantMass(const float trackpt, const float tracketa, const float trackphi,
                         const float tagpt, const float tageta, const float tagphi, const float tagE);

  float GetEta(const float theta);

  float GetPt(const float qoverp, const float theta);

  float GetDeltaZ0(const float first, const float second);

  float GetDeltaR(const float firstEta, const float firstPhi, const float secondEta, const float secondPhi );
*/
