#include <TnPSelector/TJetSelector.h>
#include <JacobUtils/LoggingUtility.h>
#include <limits>

ClassImp(TJetSelector)

// =============================================================================

TJetSelector ::
TJetSelector (const std::string& val_name)
 : name(val_name),
   isBadLooseMinusCut(0),
   emfracCut(std::numeric_limits<float>::max()),
   nTrkCut(0)
{

};

// =============================================================================

TJetSelector ::
~TJetSelector ()
{

};

// =============================================================================

int TJetSelector ::
initialize (void)
{
  return(1);
};

// =============================================================================

int TJetSelector ::
accept (const D3PDReader::JetD3PDObjectElement& jet)
{
  return(jet.isBadLooseMinus(), jet.emfrac(), jet.nTrk());
};

// =============================================================================

int TJetSelector ::
accept (const int& isBadLooseMinus, const float& emfrac, const float& nTrk)
{
  LOG_DEBUG1() << "Jet is bad minus loose: " << isBadLooseMinus;
  if(isBadLooseMinusCut != 0)
  {
    if(isBadLooseMinus != isBadLooseMinusCut) return (0);
  }

  if( (nTrk < nTrkCut && emfrac > emfracCut) ) return (0);
  return(1);
};

// =============================================================================

int TJetSelector::finalize (void)
{
  return(1);
};

// =============================================================================
