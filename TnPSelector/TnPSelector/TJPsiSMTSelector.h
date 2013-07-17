#ifndef TJPSISMTSELECTOR_H_
#define TJPSISMTSELECTOR_H_ 1

#include <D3PDReader/MuonD3PDObject.h>
#include <TString.h>

/**
 * @class TJPsiSMTSelector
 * @brief A simple selector class to apply the SMT cuts
 *
 * The accept function in this class takes a MuonD3PDObject element and returns
 * whether the muon passes the cuts or not. There is also a numerical version of
 * the accept function is available
 */
class TJPsiSMTSelector
{
public:
	/**
   * Standard ctor
   */
	TJPsiSMTSelector(const std::string& val_name="TJPsiSMTSelector");

public: 
	/**
   * Standard dtor
   */
	virtual ~TJPsiSMTSelector(void);

public:
	/**
   * Initialize
   */
	int
  initialize(void);

public:
	/**
   * Tests whether muon passes the SMT selection or not
   * @param  muon   Muon object to test
   * @return        (0, 1): Fail or Pass
   */
	int
  accept (const D3PDReader::MuonD3PDObjectElement& muon);

public:
	/**
   * Applies the selection and returns 0 or 1 on fail or pass
   * @param  d0         d0 of the muon probe
   * @param  z0sintheta z0*sin(theta) of the muon probe
   * @param  chi2       chi2 of the muon probe
   * @return            (0, 1): Fail or Pass
   */
	int
  accept (const float d0, const float z0sintheta, const float chi2);

public:
	/**
   * Does nothing for now
   * @return  Status code, 0 on fail, 1 on succeed
   */
	int
  finalize(void);

public:
	std::string name; /*< */

	// d0 Cut
  float d0Cut;

  // |z0SinTheta| cut
  float z0SinCut;

  // Chi2 cut
  float chi2Cut;
    
	ClassDef(TJPsiSMTSelector, 1);
}; // End TJPsiSMTSelector

#endif // END TJPSISMTSELECTOR_H_
