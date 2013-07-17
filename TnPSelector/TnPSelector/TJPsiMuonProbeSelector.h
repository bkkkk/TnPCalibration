#ifndef TJPSIMUONPROBESELECTOR_H_
#define TJPSIMUONPROBESELECTOR_H_ 1

// D3PDReader objects
#include <D3PDReader/MuonD3PDObject.h>
#include <D3PDReader/TrackParticleD3PDObject.h>

/**
 * @class TJPsiMuonProbeSelector
 * @brief Selector of muon probes
 *
 * Takes a probe object and matches it to all muons in a given collection based
 * on a deltaR cut.
 *
 * One can use this selector this way:
 * 
 *     TJPsiMuonProbeSelector* muonProbeSelector = new TJPsiMuonProbeSelector;
 *     muonProbeSelector->deltaRCut = 0.001
 *
 * Note that if not set, the deltaR cut is initialize in such a way as to disable
 * cut
 */
class TJPsiMuonProbeSelector
{
public:
	/**
   * Standard constructor, initializes variables so cuts are disabled 
   */
	TJPsiMuonProbeSelector( const std::string& val_name="TJPsiMuonProbeSelector" );

public:
	/**
   * Standard Destructor
   */
	virtual ~TJPsiMuonProbeSelector( void );

public:
	/**
   * Does nothing
   *
   * @return (0, 1): Fail or Pass
   */
	int
  initialize( void );

public:
	/**
   * Test if the probe track matches a combined muon within a DR range
   *
   * @param probe         TrackParticle object
   * @param muons         Muon object collection
   * @param muonProbeIdx  Get the Muon index (from muon collection) of the 
   *                      matched muon
   * @return              (0, 1): Pass or fail
   */
	int
  accept( const D3PDReader::TrackParticleD3PDObjectElement& probe,
          const D3PDReader::MuonD3PDObject& muons,
		      int& muonProbeIdx );

public:
	/**
   * Test if the probe track matches MuonProbe given DeltaR
   *
   * @param deltaR  DeltaR between probe and tag
   * @return        (0, 1): Pass or fail
   */
	int
  accept( const float& deltaR );

public:
	/**
   * Currently empty, but can be run to clear any objects needed
   * 
   * @return  Since it's currently empty it returns 1
   */
	int
  finalize( void );

private:
	/**
   * Returns the DeltaR distrance between Muon object and a track object
   * 
   * @param  probe TrackParticle object
   * @param  muon  Muon object
   * @return       The deltaR = sqrt(dEta^2 + dPhi^2)
   */
	float
  GetDeltaR( const D3PDReader::TrackParticleD3PDObjectElement& probe,
				     const D3PDReader::MuonD3PDObjectElement& muon );

public:
	std::string name; ///< Name of algorithm
	float deltaRCut;  ///< Matching DR cut

  // Needed here to send alg to node
	ClassDef(TJPsiMuonProbeSelector, 1);
};

#endif // TJPSIMUONPROBESELECTOR_H_
