#ifndef TJPSI_CLASSIFIER_H_
#define TJPSI_CLASSIFIER_H_ 1

/// Selectors
#include <TnPSelector/TMCPSelector.h>
#include <TnPSelector/TJPsiPairSelector.h>
#include <TnPSelector/TJPsiProbeSelector.h>
#include <TnPSelector/TJPsiTagSelector.h>
#include <TnPSelector/TJPsiMuonProbeSelector.h>
#include <TnPSelector/TJPsiSMTSelector.h>

class TJPsiClassifier
{
public:
  TJPsiClassifier(const std::string& val_name="JPsi");

public:
  virtual ~TJPsiClassifier();

public:
  // Test if all selectors are initialized
  int initialize(void);

public:
  //
  int classify( const D3PDReader::MuonD3PDObject& muons,
                const D3PDReader::TrackParticleD3PDObject& tracks );

public:
  // Clear counts, index lists and indexes
  int clear(void);

public:
  // 
  const std::pair<int, int>& GetSelectedPair( void );

public: 
  // Returns the index to the selected probe
  int GetSelectedProbe ( void );

public:
  // Returns the index to the selected tag
  int GetSelectedTag (void);

public:
  // Returns the index to the selected muon probe
  int GetMatchedMuonProbe (void);

public:
  //
  int GetSelectedMuonProbe(void) {
    return (muonProbeIdx);
  } 

public:
  // Returns the dz0 of the pair
  float GetDZ0 (void) { return (smallestDZ0); }

public:
  // Returns 1 if the probe is a MuonProbe
  int IsPairMuonProbe (void);

public:
  // Returns 1 if the probe is an SMT muon
  int IsPairSMT (void);

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
  TMCPSelector* mcpSelector; ///< MCP Selector
  TJPsiTagSelector* tagSelector; ///< Tag Selector
  TJPsiPairSelector* pairSelector; ///< Pair Selector
  TJPsiProbeSelector* probeSelector; ///< Probe Selector
  TJPsiMuonProbeSelector* muonProbeSelector; ///< Muon Probe Selector
  TJPsiSMTSelector* smtSelector; ///< SMT Selector


  ClassDef(TJPsiClassifier,1)
};

#endif
