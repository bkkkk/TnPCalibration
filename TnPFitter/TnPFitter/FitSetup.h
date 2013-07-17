#ifndef TNPFITTER_FITSETUP_H_
#define TNPFITTER_FITSETUP_H_ 1

#include "TnPFitter/FitConfig.h"
#include "TnPFitter/DoubleGausFit.h"

class TH1F;

class FitSetup
{
public:
	FitSetup(TH1F* histogram);
	
public:
	~FitSetup();

public:
	bool BuildFitConfiguration();

public:
	bool RunFit();

private:
	TH1F* histo;
	FitConfig* fitConfig;

ClassDef(FitSetup, 1)
};

#endif