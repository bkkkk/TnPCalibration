#ifndef TJPSIPAIRSELECTOR_H_
#define TJPSIPAIRSELECTOR_H_ 1

#include <D3PDReaderAdapter/IMuon.h>
#include <D3PDReaderAdapter/ITrack.h>
#include <string>

class TJPsiPairSelector
{
public:
  TJPsiPairSelector(const std::string& val_name="TJPsiPairSelector");

public:
  virtual ~TJPsiPairSelector(void);

  int initialize(void);

  int accept( const IMuon& tag, const IMuon& muonProbe );

  int accept( const IMuon& tag,
              const ITrack& probe );

  int accept( const float& deltaR, const float& sign, const float& invMass, 
              const float& deltaZ0 );

  int finalize(void);

private:
  float GetDeltaZ0( const float& first, const float& second );

public:
  std::string name;

  float   deltaRCutMax;
  float   deltaRCutMin;
  float   signCut;
  float   minMassCut;
  float   maxMassCut;
  float   deltaZ0Cut;

#ifdef __CINT__
  ClassDef(TJPsiPairSelector, 1);
#endif
};

#endif
