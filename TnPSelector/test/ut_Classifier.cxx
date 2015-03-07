#include "ut_Classifier.h"
#include "TnPSelector/TMCPSelector.h"
#include "TnPSelector/TJPsiTagSelector.h"
#include "TnPSelector/TJPsiPairSelector.h"
#include "TnPSelector/TJPsiProbeSelector.h"
#include "TnPSelector/TJPsiMuonProbeSelector.h"
#include "TnPSelector/TJPsiSMTSelector.h"

#include "FakeTracks.h"
#include "FakeTrack.h"
#include "FakeMuons.h"
#include "FakeMuon.h"

TEST_F(TestClassifier, ConstructingEmptyClassifierShouldReturnZero) {
  classifier = new TJPsiClassifier();
  EXPECT_EQ(0, classifier->initialize());
}

TEST_F(TestClassifier, ConstructingFilledClassifierShouldReturnOne) {
  EXPECT_EQ(1, classifier->initialize());
}

TEST_F(TestClassifier, ClassifySingleTrackThatIsAProbe) {
  FakeTrack probeTrack;
  probeTrack.constructGoodProbe();

  FakeTrack badProbe;
  badProbe.constructBadProbe();

  auto tracks = FakeTracks {
    probeTrack, badProbe, badProbe
  };

  classifier->classifyProbes(tracks);

  EXPECT_EQ(1ul, classifier->getProbeIndexes().size());
}

TEST_F(TestClassifier, ClassifySingleMuonThatIsATag) {
  auto muons = FakeMuons {
    FakeMuon::ConstructGoodTagMuon(),
    FakeMuon::ConstructGoodTagMuon(),
    FakeMuon::ConstructGoodTagMuon()
  };

  classifier->classifyTags(muons);

  EXPECT_EQ(3ul, classifier->getTagIndexes().size());
}

// Initial attempt to get function into harness
TEST_F(TestClassifier, ClassifyPairsWhenThereArentAny) {
  auto muons = FakeMuons {
    FakeMuon::ConstructGoodTagMuon()
  };

  FakeTrack probeTrack;
  probeTrack.constructGoodProbe();

  FakeTrack badProbe;
  badProbe.constructBadProbe();

  auto tracks = FakeTracks {
    probeTrack,
    badProbe,
    badProbe
  };

  classifier->classifyTags(muons);
  classifier->classifyProbes(tracks);
  auto pair = classifier->classifyPairs(muons, tracks);
  EXPECT_EQ(pair.first, -99999);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}

/*
int classify(const IMuons& muons, const ITracks& tracks);
void choosePair(const IMuons& muons, const ITracks& tracks);
void setProbePassedLevel();

int clear();
*/
