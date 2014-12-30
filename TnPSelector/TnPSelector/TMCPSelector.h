#ifndef TMCPSELECTOR_H_
#define TMCPSELECTOR_H_ 1

#include <D3PDReaderAdapter/IMuon.h>
#include <D3PDReaderAdapter/ITrack.h>
#include <TString.h>

class TMCPSelector {
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
	int accept(const IMuon& muon);

public:
	/// Test if muon passes MCP cuts
	int accept(const ITrack& track);

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

#ifdef __CINT__
ClassDef(TMCPSelector,1);
#endif

}; // End TMCPSelector

#endif // END TMCPSELECTOR_H_
