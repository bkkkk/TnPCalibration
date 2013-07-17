#ifndef TTRIGGER_MATCHING_H_
#define TTRIGGER_MATCHING_H_ 1

#include <D3PDReader/TrackParticleD3PDObject.h>
#include <D3PDReader/MuonD3PDObject.h>
#include <D3PDReader/TrigMuonEFInfoD3PDObject.h>

#include <TString.h>

class TTriggerMatching
{
public:
	/// Standard ctor
	TTriggerMatching(const std::string& val_name="TTriggerMatching");

public:
	/// Standard dtor
	virtual ~TTriggerMatching();

public:
	/// Initialize
	int initialize(void);

public:
	/// Test if muon passes
	int accept( const D3PDReader::MuonD3PDObjectElement& muon,
              const D3PDReader::TrigMuonEFInfoD3PDObject& trigMuonEF );

public:
	/// Finalize stuff
	int finalize(void);

public:
	std::string name;

public:
  float dRCut;

	ClassDef(TTriggerMatching, 1);
}; // End TTriggerMatching

#endif // END TTRIGGER_MATCHING_H_
