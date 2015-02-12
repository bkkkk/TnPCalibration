#ifndef TJPSITASELECTOR_H_
#define TJPSITASELECTOR_H_ 1

#include <D3PDReaderAdapter/IMuon.h>
#include <TString.h>

class TJPsiTagSelector {
public:
  struct TagCuts {
    float   etaCut;
    int     combinedMuonCut;
    float   trackMatchDrCut;
    float   ptCut;
    float   d0Cut;
    float   z0Cut;
    float   d0SigCut;
    float   z0SigCut;
  };

public:
	TJPsiTagSelector();
  TJPsiTagSelector(const TagCuts& cuts);
	virtual ~TJPsiTagSelector();

public:
	const bool initialize() const;
	int accept(const IMuon& muon);
	const int finalize(void) const;

public:
  inline const int accept(float eta, int combinedMuon, float pt,
                          float d0, float z0, float d0Sig, float z0Sig) const {
    if(!passReconstructionCuts(pt, eta)) return 0;
    if(!passCombinedCut(combinedMuon)) return 0;
    if(!passIPCuts(d0, z0, d0Sig, z0Sig)) return 0;

    return (1);
  }


  inline const bool passReconstructionCuts(float pt, float eta) const {
    return (pt > ptCut && fabs(eta) < etaCut);
  }

  inline const bool passCombinedCut(bool isCombined) const {
    return (isCombined == combinedMuonCut);
  }

  inline const bool passIPCuts(float d0, float z0, float d0Sig, float z0Sig) const {
    if(fabs(d0) > d0Cut) return false; 
    if(fabs(z0) > z0Cut) return false;

    if(fabs(z0Sig) > z0SigCut) return false;
    if(fabs(d0Sig) > d0SigCut) return false;

    return true;
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
