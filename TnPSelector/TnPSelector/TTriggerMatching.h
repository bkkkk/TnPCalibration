#ifndef TTRIGGER_MATCHING_H_
#define TTRIGGER_MATCHING_H_ 1

#include <D3PDReaderAdapter/ITracks.h>
#include <D3PDReaderAdapter/IMuons.h>
#include <D3PDReaderAdapter/ITrigMuons.h>

#include <TString.h>

class TTriggerMatching {
public:
	TTriggerMatching(const std::string& val_name="TTriggerMatching");
	virtual ~TTriggerMatching();

public:
	int initialize();
	int accept(const IMuon& muon, const ITrigMuons& trigMuonEF);
	int finalize();

public:
	std::string name;

public:
  float dRCut;

#ifdef __ROOT_VERSION__
	ClassDef(TTriggerMatching, 1);
#endif
};

#endif
