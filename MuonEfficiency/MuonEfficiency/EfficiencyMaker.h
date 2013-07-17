/*
 * EfficiencyMaker.h
 *
 *  Created on: 25 Oct 2011
 *      Author: neil
 */

#ifndef EFFICIENCYMAKER_H_
#define EFFICIENCYMAKER_H_

#include "TROOT.h"
#include "MuonEfficiency/SingleGausFit.h"
#include "MuonEfficiency/FitResults.h"
#include "TH1.h"

class EfficiencyMaker {
private:
	SingleGausFit* m_fitObj;
	FitResults* m_inDetFitResult;
	FitResults* m_muProbeFitResult;
	FitResults* m_matchChi2FitResult;
	TH1F* m_inDetHisto;
	TH1F* m_muProbeHisto;
	TH1F* m_matchChi2Histo;

	double m_recoEff;
	double m_recoEffStatErr;
	double m_recoEffSysErr;
	double m_matchEff;
	double m_matchEffStatErr;
	double m_matchEffSysErr;

public:
	EfficiencyMaker(TString prefixName, TString tagName, TH1F* inDetHisto, TH1F* muProbeHisto, TH1F* matchChi2Histo, int Nsigma);
	virtual ~EfficiencyMaker();

	double recoEff() { return m_recoEff; }
	double recoEffStatErr() { return m_recoEffStatErr; }
	double recoEffSysErr() { return m_recoEffSysErr; }
	double matchChi2Eff() { return m_matchEff; }
	double matchChi2EffStatErr() { return m_matchEffStatErr; }
	double matchChi2EffSysErr() { return m_matchEffSysErr; }

	ClassDef(EfficiencyMaker,1)
};

#endif /* EFFICIENCYMAKER_H_ */
