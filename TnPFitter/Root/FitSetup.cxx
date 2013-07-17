#include "TnPFitter/FitSetup.h"

ClassImp(FitSetup)

//__________________________________________________________________________
FitSetup::FitSetup(TH1F* histogram)
 : histo(histogram),
   fitConfig(NULL)
{

};


//__________________________________________________________________________
FitSetup::~FitSetup()
{

};


//__________________________________________________________________________
bool FitSetup::BuildFitConfiguration()
{
	double lowLimits = 2.6;

	int bin = histo->FindBin(lowLimits);
	LOG_INFO() << "Low limit: " << lowLimits << " in bin " << bin;
	std::vector<ROOT::Fit::ParameterSettings> pars;

	pars.push_back( ROOT::Fit::ParameterSettings("Narrow N", histo->GetMaximum(), 0, 0.0001, 10000000));
    pars.push_back( ROOT::Fit::ParameterSettings("Narrow Mean", 3.097, 0, 2.8, 3.3) );
    pars.push_back( ROOT::Fit::ParameterSettings("Narrow Sigma", 0.1, 0, 0.02, 0.2) );
    
    pars.push_back( ROOT::Fit::ParameterSettings("Wide N", histo->GetMaximum(), 0, 0.0001, 10000000));
    pars.push_back( ROOT::Fit::ParameterSettings("Wide Mean", 3.097, 0, 2.8, 3.3) );
    pars.push_back( ROOT::Fit::ParameterSettings("Wide Sigma", 0.2, 0, 0.05, 0.3) );

    std::string polyPlusDoubleGaus = "gaus(0) + gaus(3) + [6] + [7] * x + [8] * x * x";
	std::string doubleGaus = "gaus(0) + gaus(3)";
	std::string poly = "[0] + [1] * x + [2] * x * x";

	if(histo->GetBinContent( bin ) < 10)
	{	
		LOG_INFO() << "====> LOW BACKGROUND MODE";
		fitConfig = new FitConfig(doubleGaus, 6, true);
	} else
	{
		LOG_INFO() << "====> HIGH BACKGROUND MODE";
		fitConfig = new FitConfig(polyPlusDoubleGaus, 9, false);
		pars.push_back( ROOT::Fit::ParameterSettings("Constant", 0) );
		pars.push_back( ROOT::Fit::ParameterSettings("Slope", 0) );
		pars.push_back( ROOT::Fit::ParameterSettings("Poly", 0) ); 
	};

	fitConfig->SetParamsSettings(pars);
	fitConfig->SetFitOptions("MERB");

	return(true);
};


//__________________________________________________________________________
bool FitSetup::RunFit()
{
	DoubleGausFit* fit = new DoubleGausFit("Fitter", histo, *fitConfig);
	if(fit == NULL)
	{
		return (false);
	}

	LOG_INFO() << "Running Fit";
	fit->fitCompositeFunction();
	fit->setSignalFunction();
	fit->setBackgroundFunction();
    fit->Draw();

    return (true);
};
