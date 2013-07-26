#include "TnPFitter/FitConfig.h"

ClassImp(FitConfig)

//__________________________________________________________________________________________
FitConfig::
FitConfig(const std::string& function, unsigned int npar, bool isLowBkg)
 : fFitOptions("MERQB"),
   fFunction(function),
   fLowBackground(isLowBkg),
   fSettings(std::vector<ROOT::Fit::ParameterSettings>(npar)),
   firstBkgIndx(0)
{

}

//__________________________________________________________________________________________
FitConfig::
~FitConfig()
{

}

//__________________________________________________________________________________________
void FitConfig::
SetFromFitResult (const TFitResultPtr& rhs)
{
	unsigned int npar = (*rhs).NPar();

	if(npar != fSettings.size())
	{
		LOG_WARNING() << "Fit result object is not compatible with this configuration";
	}

	const double* pars = (*rhs).GetParams();

	// Loop over paramaters
	for(size_t parIdx = 0; parIdx != npar; parIdx++)
	{
		std::string name = (*rhs).GetParameterName(parIdx);
		fSettings.push_back(ROOT::Fit::ParameterSettings(name, pars[parIdx]));
	}

	return;
}

