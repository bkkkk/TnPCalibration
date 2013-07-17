#ifndef KINEMATICUTILS_H_
#define KINEMATICUTILS_H_ 1

// LorentzVector Class
#include <TLorentzVector.h>

//! Namespace for all tools and selectors used by TnPSelectors Package
namespace TNP
{
  /**
   * Constructs and returns a TVector3 object from kinematic inputs
   *
   * @param pt The momentum of the track
   * @param eta The Eta component of the track
   * @param phi The Phi component of the track
   * @return
   *   Formed TVector3 object
   */
	TVector3
  GetTrack3Vector (const float pt, const float eta, const float phi);

  /**
   * Constructs a four-vector from kinematic inputs
   *
   * @param pt The momentum of the track
   * @param eta The Eta component of the track
   * @param phi The Phi component of the track
   * @return
   *   Formed TVector object
   */
	TLorentzVector
  GetTrackVector(const float pt, const float eta, const float phi);

  /**
   * Constructs a four-vector based on muon kinematic input, used this when E 
   * is know
   * 
   * @param  pt   Muon momentum
   * @param  eta  Muon Eta
   * @param  phi  Muon Phi
   * @param  E    Muon Energy
   * @return      Formed Four-vector (TLorentzVector)
   */
	TLorentzVector
  GetMuonVector(const float pt, const float eta, const float phi, const float E);

  /**
   * Returns a 3-vector using kinematic inputs
   * 
   * @param  pt   Muon momentum
   * @param  eta  Muon eta
   * @param  phi  Muon phi
   * @return      Formed 3-vector
   */
	TVector3
  GetMuon3Vector(const float pt, const float eta, const float phi);

  /**
   * Returns the invariant mass of two objects based on kinematic parameters
   * @param  trackpt  pT of the Track
   * @param  tracketa eta of the Track
   * @param  trackphi phi of the Track
   * @param  tagpt    pT of the Tag
   * @param  tageta   eta of the Tag
   * @param  tagphi   phi of the Tag
   * @param  tagE     Energy of the Tag
   * @return          Invariant mass of tag and probe pair
   */
	float
  GetInvariantMass(const float trackpt, const float tracketa, const float trackphi,
                   const float tagpt, const float tageta, const float tagphi,
                   const float tagE);

  /**
   * Calculates and returns eta based on theta
   * @param  theta Theta value
   * @return       Corresponding eta
   */
	float
  GetEta(const float theta);

  /**
   * Returns the pT value based on the qoverp and the theta angle
   * @param  qoverp Q/P of the particle
   * @param  theta  Theta angle
   * @return        Transverse momentum
   */
	float
  GetPt(const float qoverp, const float theta);

  /**
   * Calculates the difference between the z0 IP of two particles
   * @param  first  Z0 value of one particle
   * @param  second Z0 value of the other particle
   * @return        Difference in z0
   */
  float
  GetDeltaZ0(const float first, const float second);

  /**
   * Get DeltaR
   * @param  firstEta  Eta of first
   * @param  firstPhi  Phi of first
   * @param  secondEta Eta of second
   * @param  secondPhi  Phi of second
   * @return           DeltaR
   */
  float
  GetDeltaR( const float firstEta, const float firstPhi,
             const float secondEta, const float secondPhi );
}; // End of namespace TNP

#endif // KINEMATICUTILS_H_
