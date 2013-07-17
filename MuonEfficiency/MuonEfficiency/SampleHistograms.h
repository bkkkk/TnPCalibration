#ifndef MuonEfficiency_SampleHistograms_H
#define MuonEfficiency_SampleHistograms_H

// EL
#include <EventLoop/Algorithm.h>
#include <D3PDReader/Event.h>

// Root
#include <TH1F.h>

/// Selectors
#include <TnPSelector/TJPsiClassifier.h>
#include <TnPSelector/TTriggerMatching.h>

/// Weighting
#include <MuonEfficiency/EventWeighting.h>
#include <MuonEfficiency/HistogramCollector.h>

#include <PATCore/TAccept.h>

namespace TT
{
  class TruthMuonMatching;
}

class SampleHistograms : public EL::Algorithm
{
public:
  D3PDReader::Event* event; //!

public:
  std::string outputName;

public:
  unsigned int eventCount; //!
  float nDebugEvents;
  unsigned int pairsMatched; //!
  unsigned int pairsNotMatched; //!
  float lowCut;
  float highCut;
  int doPU;

public:
  /// Histogram Collector
  HC::HistogramCollector* histosCollector; //!

public:
  // TJPsi Classifier
  TJPsiClassifier* jpsiClassifier;

public:
  EventWeighting* eventWgt;

public:
  /// This is a standard constructor
  SampleHistograms ();

public:
  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

private:
  int FillHistograms( const D3PDReader::MuonD3PDObjectElement& tag,
                      const D3PDReader::TrackParticleD3PDObjectElement& probe,
                      const float& mu,
                      const float& weight,
                      const int& muonProbeIdx );

private:
  /// Invariant mass helper function
  float GetInvariantMass (const D3PDReader::MuonD3PDObjectElement& tag,
                          const D3PDReader::TrackParticleD3PDObjectElement& probe);

private:
  ///
  int CreateAllTypesHisto(const std::string& baseName,
                          const std::string& baseTitle,
                          const unsigned int nbins,
                          const float min,
                          const float max);

  ///
  int CreateZ0Slices( const std::string& name,
                       const std::string& title,
                       const unsigned int nbins,
                       const float min,
                       const float max );

  // this is needed to distribute the algorithm to the workers
  ClassDef(SampleHistograms, 1);
};

#endif
