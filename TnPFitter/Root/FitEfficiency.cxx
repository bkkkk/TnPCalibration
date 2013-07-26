#include "TnPFitter/FitEfficiency.h"
#include "TnPFitter/DoubleGausFit.h"
#include "TnPFitter/FitIntegral.h"
#include "JacobUtils/LoggingUtility.h"
#include "TH1F.h" 

//______________________________________________________________________________
FitEfficiency::
FitEfficiency(const std::string& name, TH1F* probeHisto, TH1F* muonProbeHisto, TH1F* smtHisto)
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

  fProbeIntegral = new FitIntegral(probeName, probeHisto);
  fMuonProbeIntegral = new FitIntegral(muonProbeName, muonProbeHisto);
  fSmtIntegral = new FitIntegral(smtName, smtHisto);
}

//______________________________________________________________________________
FitEfficiency::
~FitEfficiency()
{

}

//______________________________________________________________________________
double FitEfficiency::
GetSMTError(void)
{
  return(TNPFITTER::GetTotalUncertainty(fSmtIntegral, fMuonProbeIntegral));
};

//______________________________________________________________________________
double FitEfficiency::
GetSMTEfficiency(void)
{
  LOG_DEBUG2() << "SMT efficiency: ";
  return(TNPFITTER::GetEfficiency(fSmtIntegral, fMuonProbeIntegral));
};

//______________________________________________________________________________
double FitEfficiency::
GetRecoError(void)
{
  return(TNPFITTER::GetTotalUncertainty(fMuonProbeIntegral, fProbeIntegral));
};

//______________________________________________________________________________
double FitEfficiency::
GetRecoEfficiency(void)
{
  LOG_DEBUG2() << "Reco efficiency: ";
  return(TNPFITTER::GetEfficiency(fMuonProbeIntegral, fProbeIntegral));
};

//______________________________________________________________________________
// Convenience functions

//______________________________________________________________________________
double TNPFITTER::
GetEfficiency(FitIntegral* top, FitIntegral* bottom)
{
  double topYield = top->GetCorrectedYield();
  double bottomYield = bottom->GetCorrectedYield();
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
GetTotalUncertainty(FitIntegral* top, FitIntegral* bottom)
{
  return(TNPFITTER::GetTotalUncertainty(top->GetTotalUncertainty(), bottom->GetTotalUncertainty()));
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