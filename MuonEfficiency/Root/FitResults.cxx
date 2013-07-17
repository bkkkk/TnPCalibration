/*
 * FitResults.cpp
 *
 *  Created on: 25 Oct 2011
 *      Author: neil
 */

#include <MuonEfficiency/FitResults.h>

ClassImp(FitResults)

FitResults::FitResults(	double* fitPars,
						double* fitParsErr,
						double* fitParsUp,
						double* fitParsDown,
						double compositeFuncIntegral,
						double backgroundFuncIntegral,
						double signalIntgegral_Implied,
						double compositeFuncIntegralUp,
						double backgroundFuncIntegralUp,
						double signalIntgegral_ImpliedUp,
						double compositeFuncIntegralDown,
						double backgroundFuncIntegralDown,
						double signalIntgegral_ImpliedDown) {

	m_fitPars = fitPars ;
	m_fitParsErr = fitParsErr;
	m_fitParsUp = fitParsUp;
	m_fitParsDown = fitParsDown;

	m_compositeFuncIntegral = compositeFuncIntegral;
	m_backgroundFuncIntegral = backgroundFuncIntegral;
	m_signalIntgegral_Implied = signalIntgegral_Implied;

	m_compositeFuncIntegralUp = compositeFuncIntegralUp;
	m_backgroundFuncIntegralUp = backgroundFuncIntegralUp;
	m_signalIntgegral_ImpliedUp = signalIntgegral_ImpliedUp;

	m_compositeFuncIntegralDown = compositeFuncIntegralDown;
	m_backgroundFuncIntegralDown = backgroundFuncIntegralDown;
	m_signalIntgegral_ImpliedDown = signalIntgegral_ImpliedDown;

}

FitResults::~FitResults() {
	// TODO Auto-generated destructor stub
}
