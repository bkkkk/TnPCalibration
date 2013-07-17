#ifndef SMTMiniNtuple_MiniNtupleMaker_H
#define SMTMiniNtuple_MiniNtupleMaker_H

// Event Loop
#include <EventLoop/Algorithm.h>
#include <EventLoop/StatusCode.h>
#include <EventLoopAlgs/NTupleSvc.h>

/// Selectors
#include <TnPSelector/TJPsiTagSelector.h>
#include <TnPSelector/TMCPSelector.h>

/// Trigger Selection
#include <TrigRootAnalysis/TrigDecisionToolD3PD.h>
#include <TnPSelector/TTriggerMatching.h>

// Good Runs Lists
#include <GoodRunsLists/TGoodRunsListReader.h>

// D3PDReader
#include <D3PDReader/Event.h>
#include <D3PDReader/TrackParticleD3PDObject.h>
#include <D3PDReader/triggerBitsD3PDObject.h>
#include <D3PDReader/TrigMuonEFInfoD3PDObject.h>

// Root
#include <TH1F.h>

namespace MIN
{
  class MiniNtupleMaker : public EL::Algorithm
  {
  public:
    /// Ntuple Output Object
    EL::NTupleSvc *output; //!

  public:
    /// Turn trigger cut on or off
    bool doTriggerCut;

  public:
    /// List of triggers found
    std::vector<std::string> triggersFound; //!

  public:
    /// Trigger Decision tool
    D3PD::TrigDecisionToolD3PD* tdt; //!

  public:
    /// Output Name
    std::string outputName;

public:
    /// Cutflow histogram
    TH1F* cutFlow; //!

  public:
    /// Track object for thinning the collection
    D3PDReader::TrackParticleD3PDObject out_tracks; //!

  public:
    /// Event object
    D3PDReader::Event *event; //!

  public:
    /// TGoodRunsList object
    Root::TGoodRunsList my_grl;

  public:
    /// Tag selector
    TJPsiTagSelector* tagSelector;
    TMCPSelector* mcpSelector;
    TTriggerMatching* triggerMatching;
    
  public:
    std::vector<std::string> triggerList;

  public:
    int eventCounter; //!
    int eventDebug;
    int eventInFile; //!

  public:
    // this is a standard constructor
    MiniNtupleMaker ();
  
  public:
    // these are the functions inherited from Algorithm
    virtual EL::StatusCode setupJob (EL::Job& job);
    virtual EL::StatusCode histInitialize (void);
    virtual EL::StatusCode changeInput (bool firstFile);
    virtual EL::StatusCode initialize (void);
    virtual EL::StatusCode execute (void);
    virtual EL::StatusCode postExecute (void);
    virtual EL::StatusCode finalize (void);
    virtual EL::StatusCode histFinalize (void);
    
    // this is needed to distribute the algorithm to the workers
    ClassDef(MIN::MiniNtupleMaker, 1);
  };
};

#endif
