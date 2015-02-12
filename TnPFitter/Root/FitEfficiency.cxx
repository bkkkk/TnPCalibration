#include "TnPFitter/FitEfficiency.h"
#include "TnPFitter/DoubleGausFit.h"
#include "TnPFitter/FitIntegral.h"
#include "TH1F.h"

FitEfficiency::FitEfficiency(const std::string& name,
                             TH1F* probeHisto, TH1F* muonProbeHisto, TH1F* smtHisto,
                             double min, double max)
  : fName(name) {
  if(probeHisto == nullptr) {
    throw(std::runtime_error("The probe histogram is empty"));
  }
  fProbeIntegral = new FitIntegral(name + "_probe", probeHisto, min, max);

  if(muonProbeHisto == nullptr) {
    throw(std::runtime_error("The muon probe histogram is empty"));
  }
  fMuonProbeIntegral = new FitIntegral(name + "_muonprobe", muonProbeHisto, min, max);

  if(smtHisto == nullptr) {
    throw(std::runtime_error("The SMT histogram is empty"));
  }
  fSmtIntegral = new FitIntegral(name + "_smt", smtHisto, min, max);

}

FitEfficiency::FitEfficiency(const std::string& name,
                             FitIntegral* probeIntegral,
                             FitIntegral* muonProbeIntegral,
                             FitIntegral* smtIntegral)
  : fName {name}
  , fProbeIntegral {probeIntegral}
  , fMuonProbeIntegral {muonProbeIntegral}
  , fSmtIntegral {smtIntegral} {
}

FitEfficiency::~FitEfficiency() {
}

void FitEfficiency::Draw() {
  fProbeIntegral->Draw();
  fMuonProbeIntegral->Draw();
  fSmtIntegral->Draw();
}

double FitEfficiency::GetSMTError(int nSigma, int windowSize) {
  return(TNPFITTER::GetTotalUncertainty(fSmtIntegral, fMuonProbeIntegral, nSigma, windowSize));
}

double FitEfficiency::GetSMTEfficiency(int nSigma) {
  return(TNPFITTER::GetEfficiency(fSmtIntegral, fMuonProbeIntegral, nSigma));
}

double FitEfficiency::GetRecoError(int nSigma, int windowSize) {
  return(TNPFITTER::GetTotalUncertainty(fMuonProbeIntegral, fProbeIntegral, nSigma, windowSize));
}

double FitEfficiency::GetRecoEfficiency(int nSigma) {
  return(TNPFITTER::GetEfficiency(fMuonProbeIntegral, fProbeIntegral, nSigma));
}

namespace TNPFITTER {
  double GetEfficiency(FitIntegral* top, FitIntegral* bottom, int nSigma) {
    auto topYield = top->GetCorrectedYield(nSigma);
    auto bottomYield = bottom->GetCorrectedYield(nSigma);

    auto eff = GetEfficiency(topYield, bottomYield);

    return(eff);
  }

  double GetTotalUncertainty(FitIntegral* top, FitIntegral* bottom, int nSigma, int windowSize) {
    auto topUncertainty = top->GetTotalUncertainty(nSigma, windowSize);
    auto bottomUncertainty =  bottom->GetTotalUncertainty(nSigma, windowSize);
    auto totalUncerainty = GetTotalUncertainty(topUncertainty, bottomUncertainty);

    return(totalUncerainty);
  }
}

#ifdef __CINT__
ClassImp(FitEfficiency);
#endif
