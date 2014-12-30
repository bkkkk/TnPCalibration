#ifndef TJPSITASELECTOR_H_
#define TJPSITASELECTOR_H_ 1

#include <D3PDReaderAdapter/IMuon.h>
#include <TString.h>

class TJPsiTagSelector {
public:
	TJPsiTagSelector(const std::string& val_name="TJPsiTagSelector");

public:
	virtual ~TJPsiTagSelector();

	int initialize(void);

	int accept(const IMuon& muon);

	int accept(float eta, int combinedMuon, float pt,
             float d0, float z0,
             float d0Sig, float z0Sig);

	int finalize(void);

public:
	std::string name;

public:
  float   etaCut;
  int     combinedMuonCut;
  float 	trackMatchDrCut;
  float   ptCut;
  float   d0Cut;
  float   z0Cut;
  float   d0SigCut;
  float   z0SigCut;

#ifdef __CINT__
	ClassDef(TJPsiTagSelector, 1);
#endif
};

#endif // END TJPSITASELECTOR_H_
