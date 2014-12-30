#ifndef TJPSISMTSELECTOR_H_
#define TJPSISMTSELECTOR_H_ 1

#include <D3PDReaderAdapter/IMuons.h>
#include <TString.h>

class TJPsiSMTSelector {
public:
	TJPsiSMTSelector(const std::string& val_name="TJPsiSMTSelector");
	virtual ~TJPsiSMTSelector();

public:
	int initialize();
	int accept (const IMuon& muon);
	int accept (const float d0, const float z0sintheta, const float chi2);
	int finalize();

public:
	std::string name; /*< */

  float d0Cut;
  float z0SinCut;
  float chi2Cut;

#ifdef __CINT__
	ClassDef(TJPsiSMTSelector, 1);
#endif
};

#endif
