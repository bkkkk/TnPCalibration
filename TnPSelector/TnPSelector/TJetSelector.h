#ifndef TJETSELECTOR_H_
#define TJETSELECTOR_H_ 1

/// D3PD object
#include <D3PDReader/JetD3PDObject.h>

class TJetSelector
{

public:
  /// Ctor
  TJetSelector (const std::string& val_name="TJetSelector");

public:
  /// Dtor
  virtual ~TJetSelector ();

public:
  /// initialize
  int initialize (void);

public:
  ///
  int accept (const D3PDReader::JetD3PDObjectElement& jet);

public:
  /// Applies cut
  int accept (const int& isBadLooseMinus, const float& emfrac, const float& nTrk);

public:
  /// finalize
  int finalize (void);

public:
  /// Name of selector
  std::string name;

public:
  /// Is bad loose minus cut
  int isBadLooseMinusCut;
  float emfracCut;
  float nTrkCut;

  ClassDef(TJetSelector, 1)
};

#endif
