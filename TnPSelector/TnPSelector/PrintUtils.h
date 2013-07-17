#ifndef PRINTUTILS_H_
#define PRINTUTILS_H_ 1

// D3PDReader objects for muons and tracks. This makes life easier since you
// can directly pass the objects and have information printed out.
#include <D3PDReader/TrackParticleD3PDObject.h>
#include <D3PDReader/MuonD3PDObject.h>

// Encapsulate print utils convinience functions
namespace PrintUtils
{
  
  /**
   * Prints to screen summary information about the TrackParticle object
   * @param track Track object for which to print out information
   */
  void PrintInfoTrack( const D3PDReader::TrackParticleD3PDObjectElement& track );

  /**
   * Prints to screen summary information about the Muon object
   * @param muon Muon object for which to print out information
   */
  void PrintInfoMuon( const D3PDReader::MuonD3PDObjectElement& muon );

  /**
   * Prints to screen summary information about the TRACK portion of the Muon
   * object
   * 
   * @param muon Muon object for which to print out information
   */
  void PrintMuonTrackInfo( const D3PDReader::MuonD3PDObjectElement& muon );

  /**
   * Prints to screen summary isolation information
   *
   * @param muon Muon object
   */
  void PrintMuonIsoInfo( const D3PDReader::MuonD3PDObjectElement& muon );

}; // End Namespace PrintUtils

#endif // PRINTUTILS_H_
