#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <MuonEfficiency/SampleHistograms.h>
#include <TnPSelector/KinematicUtils.h>
#include <JacobUtils/LoggingUtility.h>
#include <iostream>
#include <algorithm>
#include <TruthNavigationTools/TruthMuonMatching.h>

// this is needed to distribute the algorithm to the workers
ClassImp(SampleHistograms);

SampleHistograms :: SampleHistograms ()
 : eventCount(0),
   pairsMatched(0),
   pairsNotMatched(0),
   lowCut(0.),
   highCut(0.),
   doPU(0),
   jpsiClassifier(NULL),
   eventWgt(NULL)
{  
  LOG_INFO() << "Sample histogram"; 
}

EL::StatusCode SampleHistograms :: setupJob (EL::Job& job)
{
  LOG_INFO() << "Setting up Job";
  job.useD3PDReader();

  if(!jpsiClassifier || jpsiClassifier->initialize() != 1)
  {
    LOG_ERROR() << "JPsi Classifier not configured correctly";
    return EL::StatusCode::FAILURE;
  }

  if(!eventWgt)
  {
    LOG_ERROR() << "Event weighting collection not configured correctly";
    return EL::StatusCode::FAILURE;
  };
  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SampleHistograms :: histInitialize ()
{
  LOG_INFO() << "Initializing Histograms";

  TH1::SetDefaultSumw2();

  histosCollector = new HC::HistogramCollector("SampleHistograms", wk());

  int z0bins = 75; float minZ0 = -3; float maxZ0 = 3;
  int dz0bins = 125; float minDZ0 = 0.; float maxDZ0 = 10;

  // Probe z0 Plots
  CreateAllTypesHisto("h_probe_z0_PV", "Probe z0;z0 [mm];entries", z0bins, minZ0, maxZ0);
  CreateAllTypesHisto("h_tag_z0_PV", "Tag z0;z0 [mm];entries", z0bins, minZ0, maxZ0);
  CreateAllTypesHisto("h_probe_tag_dz0_PV", "#Delta z0(t,p);min #Deltaz0(t, p) wrt PV [mm];", dz0bins, minDZ0, maxDZ0);

  histosCollector->CreateHistogram( "h_ms_id_dz0", ";#Delta z0(ME, ID) [mm];", 30, 0, 300);
  histosCollector->CreateHistogram( "h_ms_id_dd0", ";#Delta d0(ME, ID) [mm];", 30, 0, 300);
  histosCollector->CreateHistogram( "h_ms_id_dpt", ";#Delta p_{T}(ME, ID) [GeV];", 50, 0, 5);
  histosCollector->CreateHistogram( "h_ms_id_deta", ";#Delta #eta(ME, ID);", 50, 0, 0.5);
  histosCollector->CreateHistogram( "h_ms_id_dphi", ";#Delta #phi(ME, ID);", 50, 0, 0.5);

  // Biased vs Unbiased Comparison
  histosCollector->CreateHistogram( "h_tag_trackpvz0unbiased", "Tag z0 unbiased;unbiased z0 [mm];entries", z0bins, minZ0, maxZ0);
  histosCollector->CreateHistogram( "h_muonprobe_trackpvz0unbiased", "MuonProbe z0 unbiased;unbiased z0 [mm];entries", z0bins, minZ0, maxZ0);
  
  // PU
  histosCollector->CreateHistogram( "h_averageIntPerXing", "Average interactions per Crossing;#mu;Events per 0.1", 40, 0, 40 );
  histosCollector->CreateHistogram( "h_averageIntPerXingWeighted", "Weighted Average interactions per Crossing;#mu;Events per 0.1", 40, 0, 40) ;
  
  // Muon Kinematics
  histosCollector->CreateHistogram( "h_mu_staco_pt", "p_{T} of STACO muons;p_{T} [GeV]", 20, 0., 20. );
  histosCollector->CreateHistogram( "h_mu_staco_eta", "#eta of STACO muons;#mu #eta", 50, -2.5, 2.5 );
  histosCollector->CreateHistogram( "h_mu_staco_phi", "#phi of STACO muons;#mu #phi", 64, -3.2, 3.2 );
  histosCollector->CreateHistogram( "h_mu_staco_matchchi2_ndof", "Match #chi^{2};Match-#chi^{2} / N_{d.o.f}", 100, 0., 10. );
  histosCollector->CreateHistogram( "h_mu_staco_matchchi2_ndof_highNvtx", "High N_{vtx} Match #chi^{2};Match-#chi^{2} / N_{d.o.f}", 100, 0., 10. );
  histosCollector->CreateHistogram( "h_mu_staco_matchchi2_ndof_lowNvtx", "Low N_{vtx} Match #chi^{2};Match-#chi^{2} / N_{d.o.f}", 100, 0., 10. );

  // Set up some vertexing histograms
  int binsVtx = 21; float minVtx = -0.5; float maxVtx = 20.5;
  histosCollector->CreateHistogram( "h_vtx_type_wgt", "Vertex Type Counts Weighted", 7, -0.5, 6.5);
  histosCollector->CreateHistogram( "h_vtx_dummy_wgt", "No Vtx count per event weighted", binsVtx, minVtx, maxVtx );
  histosCollector->CreateHistogram( "h_vtx_primary_wgt", "Pri Vtx count per event weighted", binsVtx, minVtx, maxVtx );
  histosCollector->CreateHistogram( "h_vtx_pileup_wgt", "PileUp Vtx count per event weighted", binsVtx, minVtx, maxVtx );

  float minVtxPos = -20; float maxVtxPos = 20; int binsVtxPos = 40; 
  histosCollector->CreateHistogram( "h_vtx_position_wgt", "Position of the Primary Vertex;z;N_{vtx} Weighted",
                                    binsVtxPos, minVtxPos, maxVtxPos);

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode SampleHistograms :: changeInput (bool firstFile)
{
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode SampleHistograms :: initialize ()
{
  SET_LOG_LEVEL(kDEBUG4);
  LOG_DEBUG() << "Initializing D3PDReader";
  event = wk()->d3pdreader();
  LOG_DEBUG() << "D3PDReader Successful";

  return EL::StatusCode::SUCCESS;
}

// =============================================================================

EL::StatusCode SampleHistograms :: execute ()
{
  if( eventCount == nDebugEvents ) SET_LOG_LEVEL(kINFO);
  LOG_DEBUG() << "============ Event " << eventCount << "============";
  eventCount++;

  // Runs the classifier and returns 0 if no good pair has been found
  int goodPairFound = jpsiClassifier->classify(event->mu_staco, event->trk);

  if(goodPairFound != 1)
  {
    LOG_DEBUG() << "No good pair found";
    return EL::StatusCode::SUCCESS;
  };

  float weight = eventWgt->GetTotalWeighting(event);
  LOG_DEBUG2() << "Total Weight is: " << weight;

  int chosenProbe = jpsiClassifier->GetSelectedProbe();
  int chosenTag = jpsiClassifier->GetSelectedTag();
  int chosenMuonProbe = jpsiClassifier->GetSelectedMuonProbe();
  float smallestDZ0 = jpsiClassifier->GetDZ0();

  float averageIntPerXing = event->eventinfo.averageIntPerXing();
  float actualIntPerXing = event->eventinfo.actualIntPerXing();
  float nVtx = event->vxp.n();

  LOG_DEBUG2() << "Average Interactions per Crossing: " << averageIntPerXing;
  LOG_DEBUG2() << "Actual Interactions per Crossing: " << actualIntPerXing;
  LOG_DEBUG2() << "Number of vertices: " << nVtx;

  std::vector<int>::iterator vxpTypeItr = event->vxp.type()->begin();
  std::vector<int>::iterator vxpTypeItrLast = event->vxp.type()->end();

  unsigned int nDummyVertex = std::count(vxpTypeItr, vxpTypeItrLast, 0);
  unsigned int nPrimaryVtx = std::count(vxpTypeItr, vxpTypeItrLast, 1);
  unsigned int nPUVtx = std::count(vxpTypeItr, vxpTypeItrLast, 3);

  histosCollector->FillHistogram("h_vtx_dummy_wgt", nDummyVertex, weight);
  histosCollector->FillHistogram("h_vtx_primary_wgt", nPrimaryVtx, weight);
  histosCollector->FillHistogram("h_vtx_pileup_wgt", nPUVtx, weight);

  // Find out the type of vertexes in each event
  for(int vxpIdx = 0; vxpIdx != event->vxp.n(); vxpIdx++)
  {
    float zPos = event->vxp[vxpIdx].z();
    int type = event->vxp[vxpIdx].type();

    if(event->vxp[vxpIdx].type() == 1) histosCollector->FillHistogram("h_vtx_position_wgt", zPos, weight);
    
    histosCollector->FillHistogram("h_vtx_type_wgt", type, weight);
  }; // End for vertex

  // Fill Average Bunch Xing
  histosCollector->FillHistogram("h_averageIntPerXing", averageIntPerXing, 1);
  histosCollector->FillHistogram("h_averageIntPerXingWeighted", averageIntPerXing, weight);

  FillHistograms(event->mu_staco[chosenTag], event->trk[chosenProbe], nVtx, weight, chosenMuonProbe);

  histosCollector->FillHistogram("h_mu_staco_pt", event->mu_staco[chosenMuonProbe].pt() / 1000, weight);
  histosCollector->FillHistogram("h_mu_staco_eta", TNP::GetEta(event->mu_staco[chosenMuonProbe].id_theta()), weight);
  histosCollector->FillHistogram("h_mu_staco_phi", event->mu_staco[chosenMuonProbe].id_phi(), weight);
  histosCollector->FillHistogram("h_mu_staco_matchchi2_ndof", event->mu_staco[chosenMuonProbe].matchchi2() / event->mu_staco[chosenMuonProbe].matchndof(), weight);

  LOG_DEBUG() << "Chosen tag: " << chosenTag << " and probe: " << chosenProbe << " and MuonProbe: " << chosenMuonProbe;

  // Can only run on full NTUP_SMWZ
#if 0
  if(event->eventinfo.isSimulation() != 0)
  {
    truthMatchingTool = new TT::TruthMuonMatching(event->mc);
    truthMatchingTool->deltaRCut = 0.01;
    if(truthMatchingTool->MatchMuonPair(event->mu_staco[chosenTag], event->mu_staco[chosenMuonProbe]) == 1)
    { LOG_DEBUG() << "Pair Is Truth Matched";
    };
  };
#endif

  float dz0 = 0;
  float dd0 = 0;
  float deta = 0;
  float dpt = 0;
  float dphi = 0;

  if(event->mu_staco[chosenMuonProbe].ms_z0.IsAvailable()) dz0 = fabs( event->mu_staco[chosenMuonProbe].me_z0_exPV() - event->mu_staco[chosenMuonProbe].id_z0_exPV() );  
  if(event->mu_staco[chosenMuonProbe].ms_d0.IsAvailable()) dd0 = fabs( event->mu_staco[chosenMuonProbe].me_d0_exPV() - event->mu_staco[chosenMuonProbe].id_d0_exPV() );
  if(event->mu_staco[chosenMuonProbe].ms_theta.IsAvailable()) deta = fabs( TNP::GetEta(event->mu_staco[chosenMuonProbe].me_theta_exPV()) -  TNP::GetEta(event->mu_staco[chosenMuonProbe].id_theta_exPV()) );
  if(event->mu_staco[chosenMuonProbe].ms_qoverp.IsAvailable()) dpt = fabs( fabs(1/event->mu_staco[chosenMuonProbe].me_qoverp_exPV()) - fabs(1/event->mu_staco[chosenMuonProbe].id_qoverp_exPV()) );
  if(event->mu_staco[chosenMuonProbe].ms_phi.IsAvailable()) dphi = fabs( event->mu_staco[chosenMuonProbe].me_phi_exPV() - event->mu_staco[chosenMuonProbe].id_phi_exPV() );

  histosCollector->FillHistogram("h_ms_id_dphi", dphi, weight);
  histosCollector->FillHistogram("h_ms_id_deta", deta, weight);
  histosCollector->FillHistogram("h_ms_id_dpt", dpt / 1000, weight);
  histosCollector->FillHistogram("h_ms_id_dz0", dz0, weight);
  histosCollector->FillHistogram("h_ms_id_dd0", dd0, weight);

  histosCollector->FillHistogram("h_probe_tag_dz0_PV_wgt", smallestDZ0, weight);

  if(nVtx < lowCut)
  {
    histosCollector->FillHistogram("h_probe_tag_dz0_PV_lowNvtx", smallestDZ0, weight);
  } else if (nVtx > highCut)
  {
    histosCollector->FillHistogram("h_probe_tag_dz0_PV_highNvtx", smallestDZ0, weight);
  };

  if(event->trk[chosenProbe].pt() > 7000)
  {
    histosCollector->FillHistogram("h_probe_tag_dz0_PV_over", smallestDZ0, weight);
  } else
  {
    histosCollector->FillHistogram("h_probe_tag_dz0_PV_under", smallestDZ0, weight);
  }; // End if Probe highPt

  return EL::StatusCode::SUCCESS;
};

// =============================================================================

EL::StatusCode SampleHistograms :: postExecute ()
{
  return EL::StatusCode::SUCCESS;
}

// =============================================================================

EL::StatusCode SampleHistograms :: finalize ()
{
  return EL::StatusCode::SUCCESS;
}

// =============================================================================

EL::StatusCode SampleHistograms :: histFinalize ()
{
  return EL::StatusCode::SUCCESS;
}

// =============================================================================

float SampleHistograms ::
GetInvariantMass (const D3PDReader::MuonD3PDObjectElement& tag,
                  const D3PDReader::TrackParticleD3PDObjectElement& probe)
{
  TLorentzVector tagVector = TNP::GetMuonVector(tag.pt(), tag.eta(), tag.phi(), tag.E());
  TLorentzVector probeVector = TNP::GetTrackVector(probe.pt(), probe.eta(), probe.phi_wrtPV());

  return ((tagVector + probeVector).M()/1000);
};

// =============================================================================

int SampleHistograms :: 
CreateZ0Slices( const std::string& baseName, const std::string& baseTitle,
                const unsigned int nbins, const float min, const float max )
{
  static const float slices[] = { 0, 0.1, 0.2, 0.4, 1.0, 2.0, 4.0, 10 };

  for(int edgeIdx = 1; edgeIdx != 8; edgeIdx++)
  {
    std::stringstream strName, strTitle;
    strName << baseName << "_" << slices[edgeIdx-1] << "_" << slices[edgeIdx];
    strTitle << baseTitle << ", " << slices[edgeIdx - 1] << " < probe z0 < " << slices[edgeIdx];

    LOG_DEBUG1() << "Slice z0 Name: " << strName.str() << " with title: "
                 << strTitle.str();

    histosCollector->CreateHistogram( strName.str().c_str(), strTitle.str().c_str(), nbins, min, max );
  };

  return (1);
};

// =============================================================================

int SampleHistograms ::
CreateAllTypesHisto(const std::string& baseName, const std::string& baseTitle,
                    const unsigned int nbins, const float min, const float max)
{
  static const std::string typesName[] = { "over", "under", "lowNvtx", "highNvtx", "wgt" };
  static const std::string typesTitle[] = { "over", "under", "low N_{vertex}", "high N_{vertex}", "Weighted" };

  for(int type = 0; type < 5; type++)
  {
    histosCollector->CreateHistogram( baseName + "_" + typesName[type], 
                                     baseTitle + " " + typesTitle[type],
                                     nbins, min, max );
  };
  return (1);
};

// =============================================================================

int SampleHistograms :: 
FillHistograms( const D3PDReader::MuonD3PDObjectElement& tag,
                const D3PDReader::TrackParticleD3PDObjectElement& probe,
                const float& nVtx,
                const float& weight,
                const int& muonProbeIdx )
{
  // pT of probe
  float probe_pt = probe.pt();

  /// Grab Probe information
  float trk_z0_wrtPV = probe.z0_wrtPV();
  float tag_id_z0_wrtPV = tag.id_z0_exPV();
  
  float tag_probe_dz0_wrtPV = TNP::GetDeltaZ0(tag_id_z0_wrtPV, trk_z0_wrtPV);
  
  float tag_trackpvz0unbiased = 0;
  if(tag.trackz0pvunbiased.IsAvailable() == 1) tag_trackpvz0unbiased = tag.trackz0pvunbiased();
  float muonprobe_matchchi2_ndof = event->mu_staco[muonProbeIdx].matchchi2() / event->mu_staco[muonProbeIdx].matchndof();

  float muonprobe_trackpvz0unbiased = 0;
  if (event->mu_staco[muonProbeIdx].trackz0pvunbiased.IsAvailable()) muonprobe_trackpvz0unbiased = event->mu_staco[muonProbeIdx].trackz0pvunbiased();

  
  #if 0
  // Fill dz0 in slices of z0
  static const float slices[] = { 0, 0.1, 0.2, 0.4, 1.0, 2.0, 4.0, 10 };
  std::stringstream strName;
  for(int edgeIdx = 1; edgeIdx != 8; edgeIdx++)
  {
    std::stringstream strName, strTitle;
    strName << "h_probe_tag_dz0_PV_" << slices[edgeIdx-1] << "_" << slices[edgeIdx];    

    LOG_DEBUG1() << "Filling z0 Name: " << strName.str();

    if(trk_z0_wrtPV > slices[edgeIdx-1] && trk_z0_wrtPV < slices[edgeIdx])
    {
      histosCollector->FillHistogram(strName.str().c_str(), tag_probe_dz0_wrtPV, weight );
    };
  };
#endif

  // Fill inclusive histos
  histosCollector->FillHistogram("h_probe_z0_PV_wgt", trk_z0_wrtPV, weight);
  histosCollector->FillHistogram("h_tag_z0_PV_wgt", tag_id_z0_wrtPV, weight);
  histosCollector->FillHistogram("h_probe_tag_dz0_PV_wgt", tag_probe_dz0_wrtPV, weight);

  histosCollector->FillHistogram("h_tag_trackpvz0unbiased", tag_trackpvz0unbiased, weight);
  histosCollector->FillHistogram("h_muonprobe_trackpvz0unbiased", muonprobe_trackpvz0unbiased, weight);

  std::string label = "";

  if(probe_pt > 7000)
  {
    label = "over";
  } else
  {
    label = "under";
  }; // End if Probe highPt

  histosCollector->FillHistogram("h_tag_z0_PV_" + label, tag_id_z0_wrtPV, weight);
  histosCollector->FillHistogram("h_probe_z0_PV_" + label, trk_z0_wrtPV, weight);
  histosCollector->FillHistogram("h_probe_tag_dz0_PV_" + label, tag_probe_dz0_wrtPV, weight);

  std::string muLabel = "";

  if(nVtx < lowCut)
  {
    LOG_DEBUG2() << "Filling low nVtx: ";
    muLabel = "lowNvtx";
  } else if(nVtx > highCut)
  {
    LOG_DEBUG2() << "Filling high nVtx: ";
    muLabel = "highNvtx";
  } else
  {
    return(1);
  }

  histosCollector->FillHistogram("h_mu_staco_matchchi2_ndof_" + muLabel, muonprobe_matchchi2_ndof, weight);
  histosCollector->FillHistogram("h_tag_z0_PV_" + muLabel, tag_id_z0_wrtPV, weight);
  histosCollector->FillHistogram("h_probe_z0_PV_" + muLabel, trk_z0_wrtPV, weight);
  histosCollector->FillHistogram("h_probe_tag_dz0_PV_" + muLabel, tag_probe_dz0_wrtPV, weight);

  return (1);
};
