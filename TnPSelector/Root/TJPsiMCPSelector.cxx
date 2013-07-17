#include <TnPSelector/TMCPSelector.h>
#include <math.h>

ClassImp(TMCPSelector);

TMCPSelector::TMCPSelector(const std::string& val_name)
 : name(val_name),
   expectBLayerHitCut(1),
   nBLHitCut(0),
   sumPixCut(0),
   sumSctCut(4),
   sumHolesCut(3),
   sumTrtCut(5)
{

};

// ========================================================================

TMCPSelector::~TMCPSelector(void)
{

};

// ========================================================================

int TMCPSelector::initialize(void)
{
	return (1);
};

// ========================================================================

int TMCPSelector::finalize (void)
{
	return (1);
};

// ========================================================================

int TMCPSelector::accept(const D3PDReader::MuonD3PDObjectElement& muon)
{
	return(this->accept(muon.expectBLayerHit(),
						muon.nBLHits(),
						muon.nPixHits(),
						muon.nPixelDeadSensors(),
						muon.nSCTHits(),
						muon.nSCTDeadSensors(),
						muon.nPixHoles(),
						muon.nSCTHoles(),
						muon.nTRTHits(),
						muon.nTRTOutliers(),
						muon.eta()));
};

// ========================================================================

int TMCPSelector::accept(const D3PDReader::TrackParticleD3PDObjectElement& track)
{
	return(this->accept(track.expectBLayerHit(),
						track.nBLHits(),
						track.nPixHits(),
						track.nPixelDeadSensors(),
						track.nSCTHits(),
						track.nSCTDeadSensors(),
						track.nPixHoles(),
						track.nSCTHoles(),
						track.nTRTHits(),
						track.nTRTOutliers(),
						track.eta()));	
};

// ========================================================================

int TMCPSelector::accept(int expectBLayerHit,
		   int nBLHits,
		   int nPixHits,
		   int nPixelDeadSensors,
		   int nSCTHits,
		   int nSCTDeadSensors,
		   int nPixHoles,
		   int nSCTHoles,
		   int nTRTHits,
		   int nTRTOutliers,
		   float eta)
{
	int sumPix = nPixHits + nPixelDeadSensors;
	int sumSct = nSCTHits + nSCTDeadSensors;
	int sumHoles = nPixHoles + nSCTHoles;
	int sumTrt = nTRTHits + nTRTOutliers;

	/// These cuts are stupid
	if( expectBLayerHit != expectBLayerHitCut ) return 0;
	if( nBLHits < nBLHitCut ) return 0;
	if( sumPix < sumPixCut ) return 0;
	if( sumSct < sumSctCut ) return 0;
	if( sumHoles > sumHolesCut ) return 0;
	if( fabs(eta) > 0.1 && fabs(eta) < 1.9 )
	{
		if ( sumTrt < sumTrtCut ) return 0;
		if ( 0.9 * sumTrt < nTRTOutliers ) return 0;
	} else
	{
		if ( sumTrt > sumTrtCut )
		{
			if (0.9 * sumTrt < nTRTOutliers) return 0;
		};
	};

	return (1);
};
