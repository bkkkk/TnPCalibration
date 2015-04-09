#include <TH1F.h>
#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>

#include <MuonEfficiency/HistogramFactory.h>
#include <TnPSelector/PrintUtils.h>

#include <TnPSelector/KinematicUtils.h>
#include <JacobUtils/LoggingUtility.h>

#include <limits>
#include <iostream>
#include <algorithm>
#include <math.h>

HistogramFactory::HistogramFactory()
    : eventCount(0),
      nDebugEvents(1.),
      goodTags(0),
      goodProbes(0),
      possiblePairs(0),
      goodPairs(0),
      goodMuonProbePairs(0),
      goodSmtMuonProbePairs(0),
      jpsiClassifier(NULL),
      jetSelector(NULL),
      eventWgt(NULL),
      prefix("InvMass") {
  SET_LOG_LEVEL(kDEBUG4);
}

EL::StatusCode HistogramFactory::setupJob(EL::Job& job) {
  LOG_DEBUG1() << "Setting up job";
  job.useD3PDReader();
  LOG_DEBUG1() << "Done and all is well";
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode HistogramFactory::histInitialize() {
  TH1::SetDefaultSumw2();

  auto minMass = jpsiClassifier->pairSelector->minMassCut / 1000;
  auto maxMass = jpsiClassifier->pairSelector->maxMassCut / 1000;
  auto invMassBin = 100;

  LOG_DEBUG() << "Making histos";

  // Grab the number of slices and number of variables to slice in
  // e.g. pt 0-1,1-2,2-3,3-5
  // Columns = 4 (4 slices)
  // Rows = 1 (pT)
  auto nColumns = varSlices.GetNumberOfSlices();
  auto nRows = varSlices.GetNumberOfVariables();

  LOG_DEBUG() << "Size of matrix = " << nRows << "x" << nColumns;

  LOG_DEBUG() << "Initializing histograms";

  // A very complicated algorithm to loop over the slice matrix and create all
  // possible 1D and 2D combinations of slices
  for (auto row = 0ul; row < nRows; row++) {
    for (auto col = 0ul; col < nColumns; col++) {
      // Grab variable with index row from the list of variables in the slices
      // object as well as the slice number col
      auto varA = varSlices.varNames[row];
      auto bottom = varSlices.varMap.at(varA)[col].first;
      auto top = varSlices.varMap.at(varA)[col].second;

      if (top != kDONTREAD) {
        auto histoNameA = GetHistogramName(PROBE, varA, bottom, top);
        auto histoNameB = GetHistogramName(MUONPROBE, varA, bottom, top);
        auto histoNameC = GetHistogramName(SMT, varA, bottom, top);

        LOG_DEBUG1() << "Name of Probe 1D histogram: " << histoNameA;
        LOG_DEBUG1() << "Name of MuonProbe 1D histogram: " << histoNameB;
        LOG_DEBUG1() << "Name of SMT 1D histogram: " << histoNameC;

        // Add the 1D histograms to the output objects in the outputstream
        sliceHistos[histoNameA] =
            new TH1F(histoNameA.c_str(), "", invMassBin, minMass, maxMass);
        wk()->addOutput(sliceHistos[histoNameA]);
        sliceHistos[histoNameB] =
            new TH1F(histoNameB.c_str(), "", invMassBin, minMass, maxMass);
        wk()->addOutput(sliceHistos[histoNameB]);
        sliceHistos[histoNameC] =
            new TH1F(histoNameC.c_str(), "", invMassBin, minMass, maxMass);
        wk()->addOutput(sliceHistos[histoNameC]);

        // Start on the 2D combinations
        if (row < nRows - 1) {
          for (size_t colB = 0; colB < nColumns; colB++) {
            for (size_t rowB = row + 1; rowB < nRows; rowB++) {
              // Add Variable 2
              auto varB = varSlices.varNames[rowB];
              auto bottomB = varSlices.varMap.at(varB)[colB].first;
              auto topB = varSlices.varMap.at(varB)[colB].second;

              if (topB != kDONTREAD) {
                if (!(std::string::npos != varA.find("cone") ||
                      std::string::npos != varB.find("cone") ||
                      std::string::npos != varA.find("phi") ||
                      std::string::npos != varB.find("phi"))) {
                  auto histoNameAA = GetHistogramName(
                      PROBE, varA, bottom, top, varB, bottomB, topB);

                  auto histoNameBB = GetHistogramName(
                      MUONPROBE, varA, bottom, top, varB, bottomB, topB);

                  auto histoNameCC = GetHistogramName(
                      SMT, varA, bottom, top, varB, bottomB, topB);

                  sliceHistos[histoNameAA] = new TH1F(
                      histoNameAA.c_str(), "", invMassBin, minMass, maxMass);
                  wk()->addOutput(sliceHistos[histoNameAA]);

                  sliceHistos[histoNameBB] = new TH1F(
                      histoNameBB.c_str(), "", invMassBin, minMass, maxMass);
                  wk()->addOutput(sliceHistos[histoNameBB]);

                  sliceHistos[histoNameCC] = new TH1F(
                      histoNameCC.c_str(), "", invMassBin, minMass, maxMass);
                  wk()->addOutput(sliceHistos[histoNameCC]);
                }
              }
            }
          }
        }
      }
    }
  }

  LOG_DEBUG1() << "sliceHistos is of size: " << sliceHistos.size();

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode HistogramFactory::changeInput(bool firstFile) {
  return (EL::StatusCode::SUCCESS);
}

EL::StatusCode HistogramFactory::initialize() {
  SET_LOG_LEVEL(kDEBUG4);
  LOG_DEBUG() << "Testing selectors";

  if (!jpsiClassifier || jpsiClassifier->initialize() != 1) {
    throw std::string("No TJPsiClassifier Configured");
  }

  LOG_DEBUG() << "Initializing D3PDReader";
  event = wk()->d3pdreader();

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode HistogramFactory::execute() {
  if (eventCount == nDebugEvents)
    SET_LOG_LEVEL(kINFO);
  LOG_DEBUG() << "============ Event " << eventCount << "============";

  auto weight = eventWgt->GetTotalWeighting(event);

  auto goodPairFound = jpsiClassifier->classify(event->mu_staco, event->trk);

  if (goodPairFound != 1) {
    LOG_DEBUG() << "No good pair found";
    return EL::StatusCode::SUCCESS;
  };

  auto chosenProbe = jpsiClassifier->GetSelectedProbe();
  auto chosenTag = jpsiClassifier->GetSelectedTag();

  PrintUtils::PrintInfoTrack(event->trk[chosenProbe]);

  auto pt = event->trk[chosenProbe].pt();
  auto eta = event->trk[chosenProbe].eta();
  auto phi = event->trk[chosenProbe].phi_wrtPV();

  auto ptLabel = varSlices.GetSliceLabel("pt", pt);
  auto etaLabel = varSlices.GetSliceLabel("eta", eta);
  auto phiLabel = varSlices.GetSliceLabel("phi", phi);
  auto sideLabel = GetSideLabel(eta);

  auto jetProbeDr = 0.0f;

  std::string jetDrLabel = "";
  if (jetProbeDr != std::numeric_limits<float>::max())
    jetDrLabel = varSlices.GetSliceLabel("jetDr", jetProbeDr);

  LOG_DEBUG() << "Running with pair ==> tag: " << chosenTag << " and probe "
              << chosenProbe;

  auto invMass = this->GetInvariantMass(event->mu_staco[chosenTag],
                                        event->trk[chosenProbe]);

  fillHistograms("Probe",
                 invMass,
                 ptLabel,
                 etaLabel,
                 phiLabel,
                 sideLabel,
                 weight,
                 jetDrLabel);

  if (jpsiClassifier->isMuonProbe != 1)
    return EL::StatusCode::SUCCESS;
  LOG_DEBUG() << "Good MuonProbe Pair";

  auto muonProbeIdx = jpsiClassifier->GetMatchedMuonProbe();

  auto etcone20 = event->mu_staco[muonProbeIdx].etcone20() / 1000.;
  auto etcone30 = event->mu_staco[muonProbeIdx].etcone30() / 1000.;
  auto etcone40 = event->mu_staco[muonProbeIdx].etcone40() / 1000.;
  auto nucone20 = event->mu_staco[muonProbeIdx].nucone20();
  auto nucone30 = event->mu_staco[muonProbeIdx].nucone30();
  auto nucone40 = event->mu_staco[muonProbeIdx].nucone40();
  auto ptcone20 = event->mu_staco[muonProbeIdx].ptcone20() / 1000.;
  auto ptcone30 = event->mu_staco[muonProbeIdx].ptcone30() / 1000.;
  auto ptcone40 = event->mu_staco[muonProbeIdx].ptcone40() / 1000.;

  auto etcone20Label = varSlices.GetSliceLabel("etcone20", etcone20);
  auto etcone30Label = varSlices.GetSliceLabel("etcone30", etcone30);
  auto etcone40Label = varSlices.GetSliceLabel("etcone40", etcone40);
  auto nucone20Label = varSlices.GetSliceLabel("nucone20", nucone20);
  auto nucone30Label = varSlices.GetSliceLabel("nucone30", nucone30);
  auto nucone40Label = varSlices.GetSliceLabel("nucone40", nucone40);
  auto ptcone20Label = varSlices.GetSliceLabel("ptcone20", ptcone20);
  auto ptcone30Label = varSlices.GetSliceLabel("ptcone30", ptcone30);
  auto ptcone40Label = varSlices.GetSliceLabel("ptcone40", ptcone40);

  fillHistograms("MuonProbe",
                 invMass,
                 ptLabel,
                 etaLabel,
                 phiLabel,
                 sideLabel,
                 weight,
                 jetDrLabel,
                 etcone20Label,
                 etcone30Label,
                 etcone40Label,
                 nucone20Label,
                 nucone30Label,
                 nucone40Label,
                 ptcone20Label,
                 ptcone30Label,
                 ptcone40Label);

  if (jpsiClassifier->isSMT != 1)
    return (EL::StatusCode::SUCCESS);
  LOG_DEBUG() << "Good SMT MuonProbe Pair";

  fillHistograms("SMT",
                 invMass,
                 ptLabel,
                 etaLabel,
                 phiLabel,
                 sideLabel,
                 weight,
                 jetDrLabel,
                 etcone20Label,
                 etcone30Label,
                 etcone40Label,
                 nucone20Label,
                 nucone30Label,
                 nucone40Label,
                 ptcone20Label,
                 ptcone30Label,
                 ptcone40Label);

  ++eventCount;

  return EL::StatusCode::SUCCESS;
};

EL::StatusCode HistogramFactory::postExecute() {
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode HistogramFactory::finalize() {
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode HistogramFactory::histFinalize() {
  return EL::StatusCode::SUCCESS;
}

float HistogramFactory::GetInvariantMass(
    const D3PDReader::MuonD3PDObjectElement& tag,
    const D3PDReader::TrackParticleD3PDObjectElement& probe) {
  TLorentzVector tagVector =
      TNP::GetMuonVector(tag.pt(), tag.eta(), tag.phi(), tag.E());
  TLorentzVector probeVector =
      TNP::GetTrackVector(probe.pt(), probe.eta(), probe.phi_wrtPV());

  return ((tagVector + probeVector).M() / 1000);
}

void HistogramFactory::printLine(std::string var, float bottom, float top) {
  std::cout << " ( " << bottom << " < " << var << " < " << top << " )";
}

int HistogramFactory::fillHistograms(const std::string& level,
                                     const float invMass,
                                     const std::string& ptLabel,
                                     const std::string& etaLabel,
                                     const std::string& phiLabel,
                                     const std::string& sideLabel,
                                     float weight,
                                     const std::string& drLabel,
                                     const std::string& etcone20Label,
                                     const std::string& etcone30Label,
                                     const std::string& etcone40Label,
                                     const std::string& nucone20Label,
                                     const std::string& nucone30Label,
                                     const std::string& nucone40Label,
                                     const std::string& ptcone20Label,
                                     const std::string& ptcone30Label,
                                     const std::string& ptcone40Label) {
  std::string prefix = "InvMass_";

  LOG_DEBUG2() << "Filling for level: " << level;
  LOG_DEBUG2() << "Filling 1D portion";

  /// Accessing maps in this way is horribly unsafe
  LOG_DEBUG2() << "Label: " << prefix << ptLabel << level;
  sliceHistos[prefix + ptLabel + level]->Fill(invMass, weight);
  LOG_DEBUG2() << "Label: " << prefix << etaLabel << level;
  sliceHistos[prefix + etaLabel + level]->Fill(invMass, weight);
  LOG_DEBUG2() << "Label: " << prefix << phiLabel << level;
  sliceHistos[prefix + phiLabel + level]->Fill(invMass, weight);

  if (drLabel.empty() != 1) {
    LOG_DEBUG2() << "Label: " << prefix << drLabel << level;
    sliceHistos[prefix + drLabel + level]->Fill(invMass, weight);
  }
  if (etcone20Label.empty() != 1) {
    LOG_DEBUG2() << "Label: " << prefix << etcone20Label << level;
    sliceHistos[prefix + etcone20Label + level]->Fill(invMass, weight);
  }
  if (etcone30Label.empty() != 1) {
    LOG_DEBUG2() << "Label: " << prefix << etcone30Label << level;
    sliceHistos[prefix + etcone30Label + level]->Fill(invMass, weight);
  }
  if (etcone40Label.empty() != 1) {
    LOG_DEBUG2() << "Label: " << prefix << etcone40Label << level;
    sliceHistos[prefix + etcone40Label + level]->Fill(invMass, weight);
  }
  if (nucone20Label.empty() != 1) {
    LOG_DEBUG2() << "Label: " << prefix << nucone20Label << level;
    sliceHistos[prefix + nucone20Label + level]->Fill(invMass, weight);
  }
  if (nucone30Label.empty() != 1) {
    LOG_DEBUG2() << "Label: " << prefix << nucone30Label << level;
    sliceHistos[prefix + nucone30Label + level]->Fill(invMass, weight);
  }
  if (nucone40Label.empty() != 1) {
    LOG_DEBUG2() << "Label: " << prefix << nucone40Label << level;
    sliceHistos[prefix + nucone40Label + level]->Fill(invMass, weight);
  }
  if (ptcone20Label.empty() != 1) {
    LOG_DEBUG2() << "Label: " << prefix << ptcone20Label << level;
    sliceHistos[prefix + ptcone20Label + level]->Fill(invMass, weight);
  }
  if (ptcone30Label.empty() != 1) {
    LOG_DEBUG2() << "Label: " << prefix << ptcone30Label << level;
    sliceHistos[prefix + ptcone30Label + level]->Fill(invMass, weight);
  }
  if (ptcone40Label.empty() != 1) {
    LOG_DEBUG2() << "Label: " << prefix << ptcone40Label << level;
    sliceHistos[prefix + ptcone40Label + level]->Fill(invMass, weight);
  }

  LOG_DEBUG2() << "Filling 2D portion";
  LOG_DEBUG2() << prefix << ptLabel << etaLabel << level;
  sliceHistos[prefix + ptLabel + etaLabel + level]->Fill(invMass, weight);

  LOG_DEBUG2() << "All Done Filling";

  return (1);
}

std::string HistogramFactory::GetSideLabel(float eta) {
  if ((fabs(eta) == eta)) {
    return ("A");
  }

  return ("C");
}

std::string HistogramFactory::GetHistogramName(HistoType type,
                                               const std::string& varA,
                                               float bottomA,
                                               float topA,
                                               const std::string& varB,
                                               float bottomB,
                                               float topB,
                                               const std::string& varC,
                                               float bottomC,
                                               float topC) {
  std::string typeString = GetTypeString(type);

  std::stringstream str;

  str.setf(std::ios_base::fixed);
  str.precision(2);

  if (varA.compare("") == 0) {
    LOG_ERROR() << "Variable name is empty! please set";
    return ("");
  }

  str << prefix << "_" << varA << "_" << bottomA << "_" << topA;
  if (varB.compare("") != 0)
    str << "_" << varB << "_" << bottomB << "_" << topB;
  if (varC.compare("") != 0)
    str << "_" << varC << "_" << bottomC << "_" << topC;
  str << "_" << typeString;

  return (str.str());
}

std::string HistogramFactory::GetTypeString(const HistoType type) {
  switch (type) {
    case PROBE:
      return ("Probe");
    case MUONPROBE:
      return ("MuonProbe");
    case SMT:
      return ("SMT");
    default:
      std::cout << "WTF are you doing?!" << std::endl;
      return ("");
  }
  return ("");
}

float HistogramFactory::GetSmallestJetDr(const float probeEta,
                                         const float probePhi,
                                         const std::vector<int>& goodJets) {
  LOG_DEBUG2() << "Probe eta: " << probeEta << " phi: " << probePhi;

  float jetProbeDr = std::numeric_limits<float>::max();

  std::vector<int>::const_iterator jetIdx = goodJets.begin();
  std::vector<int>::const_iterator jetLast = goodJets.end();

  for (; jetIdx != jetLast; jetIdx++) {
    float jetEta = event->jet_AntiKt4LCTopo[*jetIdx].eta();
    float jetPhi = event->jet_AntiKt4LCTopo[*jetIdx].phi();

    float currentDr = TNP::GetDeltaR(probeEta, probePhi, jetEta, jetPhi);

    LOG_DEBUG2() << "Jet eta: " << jetEta << " phi: " << jetPhi;
    LOG_DEBUG2() << "dR(j, p) = " << currentDr;

    if (jetProbeDr > currentDr) {
      jetProbeDr = currentDr;
    }
  }

  LOG_DEBUG1() << "Smallest dR(jet, probe) = " << jetProbeDr;

  return (jetProbeDr);
}

#ifdef __CINT__
ClassImp(HistogramFactory);
#endif
