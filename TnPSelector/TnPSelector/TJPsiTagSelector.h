#ifndef TJPSITASELECTOR_H_
#define TJPSITASELECTOR_H_ 1

#include <D3PDReader/TrackParticleD3PDObject.h>
#include <D3PDReader/MuonD3PDObject.h>
#include <TString.h>

class TJPsiTagSelector
{
public:
	/// Standard ctor
	TJPsiTagSelector(const std::string& val_name="TJPsiTagSelector");

public:
	/// Standard dtor
	virtual ~TJPsiTagSelector();

public:
	/// Initialize
	int initialize(void);

public:
	/// Test if muon passes
	int accept(const D3PDReader::MuonD3PDObjectElement& muon);

public:
	/// Test if muon passes
	int accept(float eta,
			   int combinedMuon,
			   float pt,
			   float d0,
			   float z0,
			   float d0Sig,
			   float z0Sig);

public:
	/// Finalize stuff
	int finalize(void);

public:
	std::string name;

public:
	// Cut values and names
    float   etaCut;
    int     combinedMuonCut;
    float 	trackMatchDrCut;
    float   ptCut;
    float   d0Cut;
    float   z0Cut;
    float   d0SigCut;
    float   z0SigCut;

	ClassDef(TJPsiTagSelector, 1);
}; // End TJPsiTagSelector

#endif // END TJPSITASELECTOR_H_
