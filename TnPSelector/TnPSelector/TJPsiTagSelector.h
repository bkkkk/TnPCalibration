#ifndef TJPSITASELECTOR_H_
#define TJPSITASELECTOR_H_ 1

#include <D3PDReaderAdapter/IMuon.h>
#include <TString.h>

class TJPsiTagSelector {
public:
	TJPsiTagSelector(const std::string& name="TJPsiTagSelector");

public:
	virtual ~TJPsiTagSelector();

	int initialize();

	int accept(const IMuon& muon);

	const int accept(float eta, int combinedMuon, float pt, float d0, float z0,
                   float d0Sig, float z0Sig) const;

	int finalize(void);

public:
	std::string name;

public:
  inline const bool passReconstructionCuts(float pt, float eta) const {
    return (pt > ptCut && fabs(eta) < etaCut);
  }

  inline const bool passIPCuts(float d0, float z0, float d0Sig, float z0Sig) const {
    if(fabs(d0) > d0Cut) return false; 
    if(fabs(z0) > z0Cut) return false;

    if(fabs(z0Sig) > z0SigCut) return false;
    if(fabs(d0Sig) > d0SigCut) return false;

    return true;
  }

  inline const bool passCombinedCut(bool isCombined) const {
   return (isCombined == combinedMuonCut);
  }

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

#endif
