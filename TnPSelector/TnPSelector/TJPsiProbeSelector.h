#ifndef TJPSIPROBESELECTOR_H_
#define TJPSIPROBESELECTOR_H_ 1

#include "D3PDReaderAdapter/ITrack.h"

#include <string>

class TJPsiProbeSelector {
public:
	TJPsiProbeSelector(const std::string& val_name="TJPsiProbeSelector");
	virtual ~TJPsiProbeSelector();

public:
	int initialize();

	int accept (const ITrack& track);
	int accept (const float& eta, const float& p);

	int finalize();

public:
	std::string name;
  float etaCut;
  float pCut;

#ifdef __CINT__    
	ClassDef(TJPsiProbeSelector, 1);
#endif
};

#endif
