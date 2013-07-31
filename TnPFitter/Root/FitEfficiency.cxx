#include "TnPFitter/FitEfficiency.h"
#include "TnPFitter/DoubleGausFit.h"
#include "TnPFitter/FitIntegral.h"
#include "JacobUtils/LoggingUtility.h"
#include "TH1F.h"

//______________________________________________________________________________
FitEfficiency::
FitEfficiency(const std::string& name,
              TH1F* probeHisto,
              TH1F* muonProbeHisto,
              TH1F* smtHisto,
              double min,
              double max)
  : fName(name)
{
  std::string probeName = name + "_probe";
  std::string muonProbeName = name + "_muonprobe";
  std::string smtName = name + "_smt";

  LOG_DEBUG() << "Building fit objects";

  if(probeHisto == NULL || muonProbeHisto == NULL || smtHisto == NULL)
  {
    LOG_ERROR() << "Histograms not properly constructed";
    throw;
  }

  fProbeIntegral = new FitIntegral(probeName, probeHisto, min, max);
  fMuonProbeIntegral = new FitIntegral(muonProbeName, muonProbeHisto, min, max);
  fSmtIntegral = new FitIntegral(smtName, smtHisto, min, max);
}

//______________________________________________________________________________
FitEfficiency::
~FitEfficiency()
{

}

//_______________________________________________________________________________
void FitEfficiency::
Draw(void)
{
  LOG_DEBUG1() << "Drawing fits";
  fProbeIntegral->Draw();
  fMuonProbeIntegral->Draw();
  fSmtIntegral->Draw();
}

//______________________________________________________________________________
double FitEfficiency::
GetSMTError(int nSigma, int windowSize)
{
  return(TNPFITTER::GetTotalUncertainty(fSmtIntegral, fMuonProbeIntegral, nSigma, windowSize));
};

//______________________________________________________________________________
double FitEfficiency::
GetSMTEfficiency(int nSigma)
{
  LOG_DEBUG2() << "SMT efficiency: ";
  return(TNPFITTER::GetEfficiency(fSmtIntegral, fMuonProbeIntegral, nSigma));
};

//______________________________________________________________________________
double FitEfficiency::
GetRecoError(int nSigma, int windowSize)
{
  return(TNPFITTER::GetTotalUncertainty(fMuonProbeIntegral, fProbeIntegral, nSigma, windowSize));
};

//______________________________________________________________________________
double FitEfficiency::
GetRecoEfficiency(int nSigma)
{
  LOG_DEBUG2() << "Reco efficiency: ";
  return(TNPFITTER::GetEfficiency(fMuonProbeIntegral, fProbeIntegral, nSigma));
};

//______________________________________________________________________________
// Convenience functions

//______________________________________________________________________________
double TNPFITTER::
GetEfficiency(FitIntegral* top, FitIntegral* bottom, int nSigma)
{
  double topYield = top->GetCorrectedYield(nSigma);
  double bottomYield = bottom->GetCorrectedYield(nSigma);
  return(GetEfficiency(topYield, bottomYield));
};

//______________________________________________________________________________
double TNPFITTER::
GetEfficiency(double top, double bottom)
{
  double eff = top/bottom;

  LOG_DEBUG2() << "Top = " << top << ", Bottom = " << bottom;
  LOG_DEBUG2() << "Efficiency = " << eff;
  return(eff);
};

//______________________________________________________________________________
double TNPFITTER::
GetTotalUncertainty(FitIntegral* top, FitIntegral* bottom, int nSigma, int windowSize)
{
  return(TNPFITTER::GetTotalUncertainty(top->GetTotalUncertainty(nSigma, windowSize),
                                        bottom->GetTotalUncertainty(nSigma, windowSize)));
};

//______________________________________________________________________________
double TNPFITTER::
GetTotalUncertainty(double top, double bottom)
{
  double uncertainty = sqrt(top * top + bottom * bottom);
  return(uncertainty);
};

// RootCint Streamer Support
ClassImp(FitEfficiency);
