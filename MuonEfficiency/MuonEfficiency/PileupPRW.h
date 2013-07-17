#ifndef MuonEfficiency_PileupPRW_H
#define MuonEfficiency_PileupPRW_H

#include <EventLoop/Algorithm.h>
#include <D3PDReader/Event.h>
#include <PileupReweighting/TPileupReweighting.h>

class PileupPRW : public EL::Algorithm
{

public:
  D3PDReader::Event* event; //!

public:
  Root::TPileupReweighting* pileupTool; //!


  std::string outputName;

  PileupPRW ();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // this is needed to distribute the algorithm to the workers
  ClassDef(PileupPRW, 1);
};

#endif
