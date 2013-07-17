/*
 * FitResults.h
 *
 *  Created on: 25 Oct 2011
 *      Author: neil
 */

#ifndef FITRESULTS_H_
#define FITRESULTS_H_

#include "math.h"
#include "TROOT.h"

class FitResults {
private:

	double* m_fitPars;
	double* m_fitParsErr;
	double* m_fitParsUp;
	double* m_fitParsDown;

	double m_compositeFuncIntegral;
	double m_backgroundFuncIntegral;
	double m_signalIntgegral_Implied;

	double m_compositeFuncIntegralUp;
	double m_backgroundFuncIntegralUp;
	double m_signalIntgegral_ImpliedUp;

	double m_compositeFuncIntegralDown;
	double m_backgroundFuncIntegralDown;
	double m_signalIntgegral_ImpliedDown;

public:
	FitResults(	double* fitPars,
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
				double signalIntgegral_ImpliedDown);
	virtual ~FitResults();

	double constant() { return m_fitPars[0]; }
	double slope() { return m_fitPars[1]; }
	double polyFunc() { return m_fitPars[2]; }
	double N() { return m_fitPars[3]; }
	double mass() { return m_fitPars[4]; }
	double sigma() { return m_fitPars[5]; }

	double constantErr() { return m_fitParsErr[0]; }
	double slopeErr() { return m_fitParsErr[1]; }
	double polyFuncErr() { return m_fitParsErr[2]; }
	double NErr() { return m_fitParsErr[3]; }
	double massErr() { return m_fitParsErr[4]; }
	double sigmaErr() { return m_fitParsErr[5]; }

	double constantUp() { return m_fitParsUp[0]; }
	double slopeUp() { return m_fitParsUp[1]; }
	double polyFuncUp() { return m_fitParsUp[2]; }
	double NUp() { return m_fitParsUp[3]; }
	double massUp() { return m_fitParsUp[4]; }
	double sigmaUp() { return m_fitParsUp[5]; }

	double constantDown() { return m_fitParsDown[0]; }
	double slopeDown() { return m_fitParsDown[1]; }
	double polyFuncDown() { return m_fitParsDown[2]; }
	double NDown() { return m_fitParsDown[3]; }
	double massDown() { return m_fitParsDown[4]; }
	double sigmaDown() { return m_fitParsDown[5]; }

	double compositeFuncIntegral() { return m_compositeFuncIntegral; }
	double backgroundFuncIntegral() { return m_backgroundFuncIntegral; }
	double signalIntgegral_Implied() { return m_signalIntgegral_Implied; }

	double compositeFuncIntegral_StatErr() { return sqrt(m_compositeFuncIntegral); }
	double backgroundFuncIntegral_StatErr() { return sqrt(m_backgroundFuncIntegral); }
	double signalIntgegral_Implied_StatErr() { return sqrt(m_signalIntgegral_Implied); }

	double compositeFuncIntegralUp() { return m_compositeFuncIntegralUp; }
	double backgroundFuncIntegralUp() { return m_backgroundFuncIntegralUp; }
	double signalIntgegral_ImpliedUp() { return m_signalIntgegral_ImpliedUp; }

	double compositeFuncIntegralUp_StatErr() { return sqrt(m_compositeFuncIntegralUp); }
	double backgroundFuncIntegralUp_StatErr() { return sqrt(m_backgroundFuncIntegralUp); }
	double signalIntgegral_ImpliedUp_StatErr() { return sqrt(m_signalIntgegral_ImpliedUp); }

	double compositeFuncIntegralDown() { return m_compositeFuncIntegralDown; }
	double backgroundFuncIntegralDown() { return m_backgroundFuncIntegralDown; }
	double signalIntgegral_ImpliedDown() { return m_signalIntgegral_ImpliedDown; }

	double compositeFuncIntegralDown_StatErr() { return sqrt(m_compositeFuncIntegralDown); }
	double backgroundFuncIntegralDown_StatErr() { return sqrt(m_backgroundFuncIntegralDown); }
	double signalIntgegral_ImpliedDown_StatErr() { return sqrt(m_signalIntgegral_ImpliedDown); }

	ClassDef(FitResults,1)
};

#endif /* FITRESULTS_H_ */
