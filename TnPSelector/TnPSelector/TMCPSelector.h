#ifndef TMCPSELECTOR_H_
#define TMCPSELECTOR_H_ 1

#include <D3PDReader/MuonD3PDObject.h>
#include <D3PDReader/TrackParticleD3PDObject.h>
#include <TString.h>

class TMCPSelector
{
public:
	TMCPSelector(const std::string& val_name="TMCPSelector");

public:
	virtual ~TMCPSelector (void);

public:
	/// Initialize
	int initialize (void);

public:
	/// Finalize
	int finalize (void);

public:
	/// Test if muon passes MCP cuts
	int accept(const D3PDReader::MuonD3PDObjectElement& muon);

public:
	/// Test if muon passes MCP cuts
	int accept(const D3PDReader::TrackParticleD3PDObjectElement& track);

public:
	/// Test if variables pass cuts
	int accept(int expectBLayerHit,
			   int nBLHits,
			   int nPixHits,
			   int nPixelDeadSensors,
			   int nSCTHits,
			   int nSCTDeadSensors,
			   int nPixHoles,
			   int nSCTHoles,
			   int nTRTHits,
			   int nTRTOutliers,
			   float eta);
public:
	/// Name of selector
	std::string name;

public:
	/// Cut Values
	int expectBLayerHitCut;
	int nBLHitCut;
	int sumPixCut;
	int sumSctCut;
	int sumHolesCut;
	int sumTrtCut;

ClassDef(TMCPSelector,1);

}; // End TMCPSelector

#endif // END TMCPSELECTOR_H_
