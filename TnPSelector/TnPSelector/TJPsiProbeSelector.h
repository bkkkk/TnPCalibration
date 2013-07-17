#ifndef TJPSIPROBESELECTOR_H_
#define TJPSIPROBESELECTOR_H_ 1

#include <D3PDReader/TrackParticleD3PDObject.h>
#include <TString.h>

class TJPsiProbeSelector
{
public:
	/// Standard ctor
	TJPsiProbeSelector(const std::string& val_name="TJPsiProbeSelector");

public: 
	/// Standard dtor
	virtual ~TJPsiProbeSelector(void);

public:
	/// Initialize
	int initialize(void);

public:
	/// Accept
	int accept (const D3PDReader::TrackParticleD3PDObjectElement& track);

public:
	//// Accept
	int accept (const float& eta, const float& p);

public:
	/// Finalize
	int finalize(void);

public:
	/// Name
	std::string name;

	/// Probe cut values and names
  float etaCut;
  float pCut;
    
	ClassDef(TJPsiProbeSelector, 1);
}; // End TJPsiProbeSelector

#endif // END TJPSIPROBESELECTOR_H_
