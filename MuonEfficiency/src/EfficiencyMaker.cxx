/*
 * EfficiencyMaker.cpp
 *
 *  Created on: 25 Oct 2011
 *      Author: neil
 */
#ifdef DEPRECATED

#include <MuonEfficiency/EfficiencyMaker.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

ClassImp(EfficiencyMaker)

EfficiencyMaker:: 
EfficiencyMaker(TString prefixName, TString tagName,
                TH1F* inDetHisto, TH1F* muProbeHisto, TH1F* matchChi2Histo,
                int Nsigma)
 : m_fitObj(new SingleGausFit(prefixName)),
   m_inDetHisto(inDetHisto),
   m_muProbeHisto(muProbeHisto),
   m_matchChi2Histo(matchChi2Histo)
{
  std::string s;
  std::stringstream out;
  out << Nsigma;
  s = out.str();

  m_inDetFitResult = m_fitObj->fit_InDet(inDetHisto, Nsigma, prefixName + "_" + tagName + "_" + s + "Sigma" + ".pdf");
  m_muProbeFitResult = m_fitObj->fit_MuonProbe(muProbeHisto, Nsigma, prefixName + "MuonProbe_" + tagName + "_" + s + "Sigma" + ".pdf", m_inDetFitResult->sigma());
  m_matchChi2FitResult = m_fitObj->fit_MatchChi2(matchChi2Histo, Nsigma, prefixName+"MuonProbeMatchChi2_"+tagName+"_"+s+"Sigma"+".pdf", m_muProbeFitResult->sigma());

  float inDetIntegral = m_inDetFitResult->signalIntgegral_Implied(); // Central
  float inDetIntegralUp = m_inDetFitResult->signalIntgegral_ImpliedUp(); // Up
  float inDetIntegralDown = m_inDetFitResult->signalIntgegral_ImpliedDown(); // Down

  float muProbeIntegral = m_muProbeFitResult->signalIntgegral_Implied(); // Central
  float muProbeIntegralDown = m_muProbeFitResult->signalIntgegral_ImpliedDown(); // Down
  float muProbeIntegralUp = m_muProbeFitResult->signalIntgegral_ImpliedUp(); // Up

  // Match Chi2 Integrals
  float matchChi2Integral = m_matchChi2FitResult->signalIntgegral_Implied(); // Central
  float matchChi2IntegralDown = m_matchChi2FitResult->signalIntgegral_ImpliedDown(); // Down
  float matchChi2IntegralUp = m_matchChi2FitResult->signalIntgegral_ImpliedUp(); // Up

  // Reco efficiency
  m_recoEff = muProbeIntegral / inDetIntegral;

  // Uncertainties Reco
  float recoErrDownComponent = (m_recoEff - (muProbeIntegral / inDetIntegralUp));
  float recoErrUpComponent = (m_recoEff - (muProbeIntegralDown / inDetIntegral));

  // Statistical Uncertainty Reco
  if(m_recoEff < 1) m_recoEffStatErr = sqrt( m_recoEff * (1. - m_recoEff) / inDetIntegral );
  else m_recoEffStatErr = 0;

  // Systematic Uncertainty Reco
  m_recoEffSysErr = sqrt( pow( recoErrUpComponent, 2 ) +
                          pow( recoErrDownComponent, 2 ) );
  

  // Match Chi 2 Efficiency
  m_matchEff = matchChi2Integral / muProbeIntegral;

  // Uncertainty
  // Statistical Match Chi2
  if(m_matchEff < 1) m_matchEffStatErr = sqrt( m_matchEff * ( 1. - m_matchEff ) / muProbeIntegral );
  else m_matchEffStatErr = 0;

  // Systematic Match Chi2
  float chi2ErrDownComponent = m_matchEff - ( matchChi2Integral / muProbeIntegralUp );
  float chi2ErrUpComponent = m_matchEff - ( matchChi2IntegralDown / muProbeIntegral );
  m_matchEffSysErr = sqrt( pow(chi2ErrUpComponent ,2) + pow(chi2ErrDownComponent ,2) );
}

EfficiencyMaker::~EfficiencyMaker() {
  // TODO Auto-generated destructor stub
}

#endif
