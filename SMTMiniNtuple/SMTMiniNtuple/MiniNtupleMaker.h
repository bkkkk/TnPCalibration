#ifndef SMTMiniNtuple_MiniNtupleMaker_H
#define SMTMiniNtuple_MiniNtupleMaker_H

#include <EventLoop/Algorithm.h>
#include <EventLoop/StatusCode.h>
#include <EventLoopAlgs/NTupleSvc.h>

#include <TnPSelector/TJPsiTagSelector.h>
#include <TnPSelector/TMCPSelector.h>

#include <TrigRootAnalysis/TrigDecisionToolD3PD.h>
#include <TnPSelector/TTriggerMatching.h>

#include <GoodRunsLists/TGoodRunsListReader.h>

#include <D3PDReader/Event.h>
#include <D3PDReader/TrackParticleD3PDObject.h>
#include <D3PDReader/triggerBitsD3PDObject.h>
#include <D3PDReader/TrigMuonEFInfoD3PDObject.h>

#include <TH1F.h>

namespace MIN {
class MiniNtupleMaker : public EL::Algorithm {
 public:
  MiniNtupleMaker();

 public:
  virtual EL::StatusCode setupJob(EL::Job& job);
  virtual EL::StatusCode histInitialize();
  virtual EL::StatusCode changeInput(bool firstFile);
  virtual EL::StatusCode initialize();
  virtual EL::StatusCode execute();
  virtual EL::StatusCode postExecute();
  virtual EL::StatusCode finalize();
  virtual EL::StatusCode histFinalize();

 public:
  EL::NTupleSvc* output;  //!

 public:
  bool doTriggerCut;

 public:
  std::vector<std::string> triggersFound;  //!

 public:
  D3PD::TrigDecisionToolD3PD* tdt;  //!

 public:
  std::string outputName;

 public:
  TH1F* cutFlow;  //!

 public:
  D3PDReader::TrackParticleD3PDObject out_tracks;  //!

 public:
  D3PDReader::Event* event;  //!

 public:
  Root::TGoodRunsList my_grl;

 public:
  TJPsiTagSelector* tagSelector;
  TMCPSelector* mcpSelector;
  TTriggerMatching* triggerMatching;

 public:
  std::vector<std::string> triggerList;

 public:
  int eventCounter;  //!
  int eventDebug;
  int eventInFile;  //!

#ifdef __CINT__
  ClassDef(MIN::MiniNtupleMaker, 1);
#endif
};
};

#endif
