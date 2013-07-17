#ifndef TNPFITTER_FITRESULT_H_
#define TNPFITTER_FITRESULT_H_ 1

#include <map>
#include <string>

class FitResult
{
public:
	FitResult(const std::string& name, const size_t NPars)
	: fName( name )
	{
	}

public:
	~FitResult()
	{
		fName = "";
		fParameters.clear();
	}

public:
	int AddParameter(std::string name, float val, float error)
	{
		fParameters[name] = std::make_pair (val, error);
		return (1);
	}

public:
	size_t GetNPars(void) { return(fParameters.size()); }

public:
	std::map<std::string, std::pair<float, float > >& GetParameters() { return (fParameters); }

public:
	std::pair<float, float>& GetParameter(std::string parName) { return (fParameters[parName]); }

public:
	float GetParValue(const std::string& name) { return (fParameters[name].first); }

public:
	float GetParError(const std::string& name) { return (fParameters[name].second); }

private:
	// Holds parameters
	std::string fName;
	std::map<std::string, std::pair<float, float > > fParameters;
};

#endif
