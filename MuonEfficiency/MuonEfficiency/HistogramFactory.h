#ifndef MUONEFFICIENCY_SAMPLEHISTOGRAMS_H_
#define MUONEFFICIENCY_SAMPLEHISTOGRAMS_H_

#include <EventLoop/Algorithm.h>
#include <D3PDReader/Event.h>
#include <TH1F.h>

#include <MuonEfficiency/TnPSlices.h>

#include <TnPSelector/TJPsiClassifier.h>
#include <TnPSelector/TJetSelector.h>

#include <MuonEfficiency/EventWeighting.h>
#include <MuonEfficiency/SliceHisto.h>

// C++ STL
#include <map>

class HistogramFactory : public EL::Algorithm
{
public:

  /// Histogram collection
  std::map <std::string, TH1F*> sliceHistos; //!
  std::map <std::string, TH1F*> muonKinematics; //!
  std::map <std::string, TH1F*> trackKinematics; //!

public:
  /// Import event
  D3PDReader::Event* event; //!

public:
  std::string outputName;

public:
  unsigned int eventCount; //!
  double nDebugEvents;
  unsigned int goodTags; //!
  unsigned int goodProbes; //!
  unsigned int possiblePairs; //!
  unsigned int goodPairs; //!
  unsigned int goodMuonProbePairs; //!
  unsigned int goodSmtMuonProbePairs; //!

public:
  TnPSlices varSlices;

public:
  // Classifier
  TJPsiClassifier* jpsiClassifier;

public:
  /// Jet Selector
  TJetSelector* jetSelector;

public:
  // Event Weighting
  EventWeighting* eventWgt;

public:
  /// Prefix
  std::string prefix;

public:
  /// This is a standard constructor
  HistogramFactory ();
  
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

  float GetSmallestJetDr( const float probeEta, const float probePhi,
                          const std::vector<int>& goodJets );

  std::string GetSideLabel(float eta);

  void printLine(std::string var, float bottom, float top);
  
  int fillHistograms(  const std::string& level, const float invMass,
                       const std::string& ptLabel, const std::string& etaLabel,
                       const std::string& phiLabel, const std::string& sideLabel,                    
                       float weight,
                       const std::string& drLabel="",
                       const std::string& etcone20Label="", const std::string& etcone30Label="", const std::string& etcone40Label="",
                       const std::string& nucone20Label="", const std::string& nucone30Label="", const std::string& nucone40Label="",
                       const std::string& ptcone20Label="", const std::string& ptcone30Label="", const std::string& ptcone40Label="");
  

private:
  /// Invariant mass helper function
  float GetInvariantMass (const D3PDReader::MuonD3PDObjectElement& tag,
                          const D3PDReader::TrackParticleD3PDObjectElement& probe);

public:
  std::string GetHistogramName( HistoType type,
                                const std::string& varA, float bottomA, float topA,
                                const std::string& varB="", float bottomB=0., float topB=0.,
                                const std::string& varC="", float bottomC=0., float topC=0. );

public:
  // 
  std::string GetTypeString( const HistoType type );

  // this is needed to distribute the algorithm to the workers
  ClassDef(HistogramFactory, 1);


};

#endif
