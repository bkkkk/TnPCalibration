#include <TnPFitter/FitIntegral.h>
#include <TnPFitter/DoubleGausFit.h>
#include <TH1F.h>
#include <TF1.h>
#include <JacobUtils/LoggingUtility.h>

#if 0

//______________________________________________________________________________
FitIntegral::FitIntegral(DoubleGausFit* fitter)
 : 
{

}

//______________________________________________________________________________
FitIntegral::~FitIntegral()
{

}

//______________________________________________________________________________
double FitIntegral::
GetSignalIntegral()
{
	// TF1* signal = fFitter->GetSignalFunction();
	
	// double integral = signal->Integral(lowLimit, highLimit);
	double integral = 0;

	//LOG_INFO() << "Signal " << integral;

	return (integral);
}

//______________________________________________________________________________
double FitIntegral::
GetBackgroundIntegral()
{
	//TF1* background = fFitter->GetBackgroundFunction();
	
	//double integral = background->Integral(lowLimit, highLimit);
  	double integral = 0;
	// LOG_INFO() << "Background " << integral;

	return (integral);
}

//______________________________________________________________________________
double FitIntegral::
GetYield()
{
	TH1* histogram = fFitter->GetHistogram();
		
	// Get Bin Range
	int lowBin = histogram->FindBin(lowLimit);
	int highBin = histogram->FindBin(highLimit);

	double integral = histogram->Integral(lowBin, highBin);
	LOG_INFO() << "Yield: " << integral;

	return (integral);
}

//______________________________________________________________________________
double FitIntegral::
GetSignalYield()
{
	//double bkg = GetBackgroundIntegral();
	//double histoYield = GetYield();

	//double yieldMinusBkg = histoYield - bkg;

	//LOG_INFO() << "Signal Yield: " << yieldMinusBkg;

	//return(yieldMinusBkg);
}
#endif