#ifndef TJPSIPAIRSELECTOR_H_
#define TJPSIPAIRSELECTOR_H_ 1

#include <D3PDReader/MuonD3PDObject.h>
#include <D3PDReader/TrackParticleD3PDObject.h>

class TJPsiPairSelector
{
public:
	TJPsiPairSelector(const std::string& val_name="TJPsiPairSelector");

public:
	virtual ~TJPsiPairSelector(void);

public:
	/// Initialize
	int initialize(void);

public:
	/// Test if tag matches muonProbe
	int accept( const D3PDReader::MuonD3PDObjectElement& tag,
			        const D3PDReader::MuonD3PDObjectElement& muonProbe );

public:
	/// Test for tag and probe
	int accept( const D3PDReader::MuonD3PDObjectElement& tag,
			        const D3PDReader::TrackParticleD3PDObjectElement& probe );

public:
	int accept( const float& deltaR, const float& sign, const float& invMass,
              const float& deltaZ0 );

public:
	/// Finalize
	int finalize(void);

private:
  /// Calculate dz0
  float GetDeltaZ0( const float& first, const float& second );

public:
	/// Name
	std::string name;

    /// Cut values
    float   deltaRCutMax;
    float   deltaRCutMin;
    float   signCut;
    float   minMassCut;
    float   maxMassCut;
    float   deltaZ0Cut;

	ClassDef(TJPsiPairSelector, 1);
};

#endif
