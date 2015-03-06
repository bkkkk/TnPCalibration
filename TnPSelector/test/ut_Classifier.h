#ifndef TESTCLASSIFIER_H_
#define TESTCLASSIFIER_H_ 1

#include <gtest/gtest.h>

#include <TnPSelector/TJPsiClassifier.h>

class TestClassifier : public ::testing::Test {
public:
  TJPsiClassifier* classifier;

  TestClassifier() = default;

  virtual void SetUp() {
    classifier = new TJPsiClassifier();

    TJPsiTagSelector* tagSelector = new TJPsiTagSelector();
    tagSelector->etaCut = 2.5; tagSelector->combinedMuonCut = 1;
    tagSelector->ptCut = 4000; tagSelector->d0Cut = 0.3;
    tagSelector->z0Cut = 1.5; tagSelector->d0SigCut = 3.0;
    tagSelector->z0SigCut = 3.0;

    TJPsiProbeSelector* probeSelector = new TJPsiProbeSelector();
    probeSelector->etaCut = 2.5; probeSelector->pCut = 3000;

    TJPsiPairSelector* pairSelector = new TJPsiPairSelector();
    pairSelector->deltaRCutMax = 3.5; pairSelector->signCut = -1;
    pairSelector->deltaRCutMin = 0.2;
    pairSelector->minMassCut = 2000.; pairSelector->maxMassCut = 4000.;
    pairSelector->deltaZ0Cut = 2.;

    TJPsiMuonProbeSelector* muonProbeSelector = new TJPsiMuonProbeSelector();
    muonProbeSelector->deltaRCut = 0.001;

    TJPsiSMTSelector* smtSelector = new TJPsiSMTSelector();
    smtSelector->d0Cut = 3;
    smtSelector->z0SinCut = 3;
    smtSelector->chi2Cut = 3.2;

    TMCPSelector* mcpSelector = new TMCPSelector();

    classifier->mcpSelector = mcpSelector;
    classifier->tagSelector = tagSelector;
    classifier->pairSelector = pairSelector;
    classifier->probeSelector = probeSelector;
    classifier->muonProbeSelector = muonProbeSelector;
    classifier->smtSelector = smtSelector;
  }
};

#endif
