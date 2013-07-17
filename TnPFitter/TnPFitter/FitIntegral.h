#ifndef TNPFITTER_FITINTEGRAL_H_
#define TNPFITTER_FITINTEGRAL_H_ 1
	
class DoubleGausFit;

class FitIntegral
{
public:
	FitIntegral(DoubleGausFit* fitter);

public:
	~FitIntegral();

public:
	double GetSignalIntegral();

public:
	double GetBackgroundIntegral();

public:
	double GetYield();

public:
	double GetSignalYield();

private:
	DoubleGausFit* fFitter;
	double lowLimit;
	double highLimit;
};

#endif