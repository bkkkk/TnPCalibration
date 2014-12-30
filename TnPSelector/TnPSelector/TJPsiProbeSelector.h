#ifndef TJPSIPROBESELECTOR_H_
#define TJPSIPROBESELECTOR_H_ 1

#include "D3PDReaderAdapter/ITrack.h"

#include <string>

class TJPsiProbeSelector {
public:
	TJPsiProbeSelector(const std::string& val_name="TJPsiProbeSelector");
	virtual ~TJPsiProbeSelector(void);

public:
	int initialize(void);

	int accept (const ITrack& track);
	int accept (const float& eta, const float& p);

	int finalize(void);

public:
	std::string name;
  float etaCut;
  float pCut;

#ifdef __CINT__    
	ClassDef(TJPsiProbeSelector, 1);
#endif
};

#endif
