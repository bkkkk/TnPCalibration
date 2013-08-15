#ifndef PILEUPREWEIGHTING_H_
#define PILEUPREWEIGHTING_H_ 1
	
#include "MuonEfficiency/Weighting.h"
#include "PileupReweighting/TPileupReweighting.h"

class PileupReWeighting : public Weighting
{
public:
	PileupReWeighting( const std::string& name="", const std::string& title="", 
                     Root::TPileupReweighting* tool=NULL, double override = 0 );

public:
	// Dtor
	~PileupReWeighting();

public:
	// Returns weight
	double GetWeight(const D3PDReader::Event* event);
  
private:
	Root::TPileupReweighting* pileupTool;
  double channelOverride;

	ClassDef(PileupReWeighting, 1);
};

#endif