#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <MuonEfficiency/PileupPRW.h>
#include <EventLoop/OutputStream.h>

// this is needed to distribute the algorithm to the workers
ClassImp(PileupPRW)



PileupPRW :: PileupPRW () 
: pileupTool(new Root::TPileupReweighting("pileupTool"))
{
  
}



EL::StatusCode PileupPRW :: setupJob (EL::Job& job)
{
  job.useD3PDReader();

  EL::OutputStream out("outFile");
  job.outputAdd( out );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode PileupPRW :: histInitialize ()
{
  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode PileupPRW :: changeInput (bool firstFile)
{
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode PileupPRW :: initialize ()
{
  /// Make sure to set up D3PD reader
  event = wk()->d3pdreader();

  pileupTool->UsePeriodConfig("MC12a");
  pileupTool->Initialize();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode PileupPRW :: execute ()
{
  int RunNumber = event->eventinfo.RunNumber();
  int mc_channel_number = event->eventinfo.mc_channel_number();
  float averageIntPerXing = event->eventinfo.averageIntPerXing();
  
  pileupTool->Fill(RunNumber, mc_channel_number,(event->mcevt.weight())->at(0)[0],averageIntPerXing);
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode PileupPRW :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode PileupPRW :: finalize ()
{
  TFile* f = wk()->getOutputFile("outFile");
  pileupTool->WriteToFile(f);
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode PileupPRW :: histFinalize ()
{
  return EL::StatusCode::SUCCESS;
}
