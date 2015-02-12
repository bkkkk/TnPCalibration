#ifndef TJPSISMTSELECTOR_H_
#define TJPSISMTSELECTOR_H_ 1

#include <D3PDReaderAdapter/IMuons.h>
#include <TString.h>

class TJPsiSMTSelector {
public:
	TJPsiSMTSelector();
	virtual ~TJPsiSMTSelector();

public:
	int initialize();
	int accept (const IMuon& muon);
	int accept (float d0, float z0sintheta, float chi2);
	int finalize();

public:
  float d0Cut;
  float z0SinCut;
  float chi2Cut;

#ifdef __CINT__
	ClassDef(TJPsiSMTSelector, 1);
#endif
};

#endif
