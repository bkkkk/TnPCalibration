#ifndef TJPSIMUONPROBESELECTOR_H_
#define TJPSIMUONPROBESELECTOR_H_ 1

#include <D3PDReaderAdapter/IMuons.h>
#include <D3PDReaderAdapter/ITracks.h>
#include <string>

class TJPsiMuonProbeSelector {
public:
	TJPsiMuonProbeSelector(const std::string& val_name="TJPsiMuonProbeSelector");

	virtual ~TJPsiMuonProbeSelector();

	int initialize(void);

	int accept(const ITrack& probe, const IMuons& muons, int& muonProbeIdx);

	int accept(const float& deltaR);

	int finalize();

private:
	float GetDeltaR(const ITrack& probe, const IMuon& muon );

public:
	std::string name;
	float deltaRCut;

#ifdef __CINT__
	ClassDef(TJPsiMuonProbeSelector, 1);
#endif
};

#endif // TJPSIMUONPROBESELECTOR_H_
