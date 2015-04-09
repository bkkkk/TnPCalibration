#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <MuonEfficiency/PileupPRW.h>
#include <EventLoop/OutputStream.h>
#include <TFile.h>

PileupPRW::PileupPRW()
    : pileupTool(new Root::TPileupReweighting("pileupTool")) {
}

EL::StatusCode PileupPRW::setupJob(EL::Job& job) {
  job.useD3PDReader();

  EL::OutputStream out("outFile");
  job.outputAdd(out);

  return (EL::StatusCode::SUCCESS);
}

EL::StatusCode PileupPRW::initialize() {
  event = wk()->d3pdreader();

  pileupTool->UsePeriodConfig("MC12a");
  pileupTool->Initialize();

  return (EL::StatusCode::SUCCESS);
}

EL::StatusCode PileupPRW::execute() {
  auto RunNumber = event->eventinfo.RunNumber();
  auto mc_channel_number = event->eventinfo.mc_channel_number();
  auto averageIntPerXing = event->eventinfo.averageIntPerXing();

  pileupTool->Fill(RunNumber,
                   mc_channel_number,
                   (event->mcevt.weight())->at(0)[0],
                   averageIntPerXing);
  return (EL::StatusCode::SUCCESS);
}

EL::StatusCode PileupPRW::finalize() {
  TFile* f = wk()->getOutputFile("outFile");
  pileupTool->WriteToFile(f);

  return (EL::StatusCode::SUCCESS);
}

#ifdef __CINT__
ClassImp(PileupPRW)
#endif
