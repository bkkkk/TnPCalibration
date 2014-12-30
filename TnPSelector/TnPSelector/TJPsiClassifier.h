#ifndef TJPSI_CLASSIFIER_H_
#define TJPSI_CLASSIFIER_H_ 1

/// Selectors
#include <TnPSelector/TMCPSelector.h>
#include <TnPSelector/TJPsiPairSelector.h>
#include <TnPSelector/TJPsiProbeSelector.h>
#include <TnPSelector/TJPsiTagSelector.h>
#include <TnPSelector/TJPsiMuonProbeSelector.h>
#include <TnPSelector/TJPsiSMTSelector.h>

class TJPsiClassifier {
public:
  TJPsiClassifier(const std::string& val_name="JPsi");
  virtual ~TJPsiClassifier();

public:
  int initialize();

  int classify( const IMuons& muons, const ITracks& tracks );

  int clear();

  const std::pair<int, int>& GetSelectedPair();

  int GetSelectedProbe ();

  int GetSelectedTag ();

  int GetMatchedMuonProbe ();

  inline int GetSelectedMuonProbe() { return (muonProbeIdx); } 

  inline float GetDZ0 () { return (smallestDZ0); }

  int IsPairMuonProbe ();

  int IsPairSMT ();

public:
  std::string name; ///< Name of tool
  
  std::pair<int, int> pair; ///< To hold pair of tag and probe

  int isMuonProbe; ///< Is Muon Probe
  int isSMT; ///< Is SMT
  
  int muonProbeIdx; ///< Matched muon index

private:
  float smallestDZ0;

private:
  std::vector<int> probesIndexes;
  std::vector<int> tagsIndexes;

public:
  TMCPSelector* mcpSelector;
  TJPsiTagSelector* tagSelector;
  TJPsiPairSelector* pairSelector;
  TJPsiProbeSelector* probeSelector;
  TJPsiMuonProbeSelector* muonProbeSelector;
  TJPsiSMTSelector* smtSelector;

#ifdef __CINT__
  ClassDef(TJPsiClassifier,1)
#endif
};

#endif
