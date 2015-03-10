#include <SMTMiniNtuple/MiniNtupleMaker.h>
#include <iostream>

#include <JacobUtils/ReaderTools.h>

#include <JacobUtils/LoggingUtility.h>

#include <EventLoop/Job.h>
#include <EventLoop/Worker.h>

#include <TH1.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TTree.h>

ClassImp(MIN::MiniNtupleMaker);

namespace MIN {

MiniNtupleMaker::MiniNtupleMaker()
    : doTriggerCut(true),
      tagSelector(NULL),
      mcpSelector(NULL),
      triggerMatching(NULL),
      eventDebug(20) {
}

EL::StatusCode MiniNtupleMaker::setupJob(EL::Job& job) {
  job.useD3PDReader();
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode MiniNtupleMaker::histInitialize() {
  cutFlow = new TH1F("Cutflow", ";Cut;Events", 11, -0.5, 5.5);
  wk()->addOutput(cutFlow);

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode MiniNtupleMaker::changeInput(bool firstFile) {
  /// Reset in file event counter, used by trigger output system
  eventInFile = 0;

  /// Get trigger information
  TTree* trigConfTree =
      dynamic_cast<TTree*>(wk()->inputFile()->Get("physicsMeta/TrigConfTree"));
  TTree* eventTree = dynamic_cast<TTree*>(wk()->inputFile()->Get("physics"));

  if ((eventTree == NULL) || (trigConfTree == NULL)) {
    LOG_ERROR() << "Trigger Conf/Event Tree not present";
    return EL::StatusCode::FAILURE;
  } else {
    LOG_INFO() << "Trees found";
  }

  LOG_INFO() << "Creating TrigDecisionTool";

  if (firstFile != 1) {
    tdt = new D3PD::TrigDecisionToolD3PD(eventTree, trigConfTree);

    /// Check which triggers are present
    for (size_t trigIdx = 0; trigIdx != triggerList.size(); trigIdx++) {
      /// Add this trigger to a meta-data string
      if (tdt->GetConfigSvc().IsConfigured(triggerList[trigIdx]) != 0) {
        LOG_DEBUG() << "Trigger " << triggerList[trigIdx] << " found";
      }
    }
  }

  return (EL::StatusCode::SUCCESS);
}

EL::StatusCode MiniNtupleMaker::initialize() {
  SET_LOG_LEVEL(kDEBUG4);
  eventCounter = 0;

  /// Make sure to set up D3PD reader
  event = wk()->d3pdreader();

  /// Get NTupleSvc
  if (!outputName.empty()) {
    output = EL::getNTupleSvc(wk(), outputName);
  } else {
    output = 0;
  }

  TTree* trigConfTree =
      dynamic_cast<TTree*>(wk()->inputFile()->Get("physicsMeta/TrigConfTree"));
  TTree* eventTree = dynamic_cast<TTree*>(wk()->inputFile()->Get("physics"));

  tdt = new D3PD::TrigDecisionToolD3PD(eventTree, trigConfTree);

  /// Check which triggers are present
  for (size_t trigIdx = 0; trigIdx != triggerList.size(); trigIdx++) {
    /// Add this trigger to a meta-data string
    if (tdt->GetConfigSvc().IsConfigured(triggerList[trigIdx]) != 0) {
      LOG_DEBUG() << "Trigger " << triggerList[trigIdx] << " found";
      output->copyBranch(triggerList[trigIdx]);
      output->copyBranch("trig_EF_trigmuonef_" + triggerList[trigIdx]);
    }
  }

  /// Create a new track collection and add to output Ntuple
  out_tracks.SetPrefix("trk_");
  out_tracks.SetActive(kTRUE,
                       "^trk_n$|^trk_pt$|^trk_eta$|^trk_phi_wrtPV$|^trk_chi2$|^"
                       "trk_d0_wrtPV$|^trk_z0_wrtPV$|^trk_expectBLayerHit$|^"
                       "trk_nBLHits$|^trk_nPixHits$|^trk_nPixHoles$|^trk_"
                       "nPixelDeadSensors$|^trk_nSCTHits$|^trk_nSCTDeadSensors$"
                       "|^trk_nSCTHoles$|^trk_nTRTHits$|^trk_nTRTOutliers$|^"
                       "trk_ndof$|^trk_qoverp_wrtPV$|^trk_theta_wrtPV$");
  if (output) {
    out_tracks.WriteTo(output->tree());
  }

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode MiniNtupleMaker::execute() {
  // Counter for tags
  int nTags = 0;

  // Cut counter
  int cut = 0;
  cutFlow->Fill(cut);

  // Turn on debug flag
  if (eventCounter == eventDebug)
    SET_LOG_LEVEL(kWARNING);
  LOG_DEBUG() << "Event in file: " << eventInFile;

  // Check if event is MC or passes GRL
  if (!event->eventinfo.isSimulation()) {
    int passGRL = my_grl.HasRunLumiBlock(event->eventinfo.RunNumber(),
                                         event->eventinfo.lbn());

    /// Move to next event if it failed the GRL
    if (passGRL != 1) {
      eventCounter++;
      LOG_DEBUG() << "Event failed GRL";
      return EL::StatusCode::SUCCESS;
    }

    LOG_DEBUG() << "Event passed GRL";

  } else {
    LOG_DEBUG() << "This MC";
  }
  ++cut;
  cutFlow->Fill(cut);

  tdt->GetEntry(eventInFile);

  bool passedTrigger = false;

  for (size_t trigIdx = 0; trigIdx != triggerList.size(); trigIdx++) {
    if (tdt->GetConfigSvc().IsConfigured(triggerList[trigIdx]) == 1) {
      if (tdt->IsPassed(triggerList[trigIdx]) != 0) {
        LOG_DEBUG() << "Event passes trigger: " << triggerList[trigIdx];
        passedTrigger = true;
      }
    }
  }

  if (passedTrigger != 1 && doTriggerCut != 0) {
    LOG_DEBUG() << "Event hasn't passed a single trigger";
    eventCounter++;
    eventInFile++;
    return EL::StatusCode::SUCCESS;
  }

  ++cut;
  cutFlow->Fill(cut);

  // Loop over muons to find tags
  for (int muon = 0; muon != event->mu_staco.n(); ++muon) {
    LOG_DEBUG() << "Current muon = " << muon + 1 << "/" << event->mu_staco.n();
    if (tagSelector->accept(event->mu_staco[muon]) &&
        mcpSelector->accept(event->mu_staco[muon]) &&
        triggerMatching->accept(event->mu_staco[muon],
                                event->trig_EF_trigmuonef)) {
      LOG_DEBUG() << "This muon is a tag";
      ++nTags;
    }
  }

  out_tracks.Clear();

  /// Loop over the tracks and remove the ones that DONT pass the MCP cuts
  for (int track = 0; track != event->trk.n(); track++) {
    if (mcpSelector->accept(event->trk[track])) {
      out_tracks += event->trk[track];
    }  // End if mcpSelector
  }    // End for tracks

  /// Require at least one tag
  if (nTags != 0) {
    ++cut;
    cutFlow->Fill(cut);
    LOG_DEBUG() << "There is at least one tag muon, event is written";
    output->setFilterPassed();
  }

  /// Count events
  ++eventCounter;
  ++eventInFile;

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode MiniNtupleMaker::postExecute() {
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode MiniNtupleMaker::finalize() {
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode MiniNtupleMaker::histFinalize() {
  return EL::StatusCode::SUCCESS;
}
}
