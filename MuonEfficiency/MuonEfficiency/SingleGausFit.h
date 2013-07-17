
/*
 * SingleGausFit.h
 *
 *  Created on: 24 Oct 2011
 *      Author: coopers
 */

#ifndef SINGLEGAUSFIT_H_
#define SINGLEGAUSFIT_H_

#include "TH1.h"
#include "TF1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TString.h"
#include "TFile.h"
#include "FitResults.h"
#include "TString.h"
#include "TVirtualFitter.h"

class SingleGausFit {

 private:
  // Create and setup the fitting fucntions
  void setCompositeFitFunc();
  void setCompositeFitFunc(double inputSigma);
  
  void setBackgroundFitFunc();
  
  void setSignalFitFunc();
  
  void setSigmaRanges();
  void setSigmaRanges(double inputSigma);
  
  void setIntegrals();
  
  void setCompositeFitFuncUpErr();
  void setCompositeFitFuncDownErr();
  
  void setBackgroundFitFuncUpErr();
  void setBackgroundFitFuncDownErr();

  double m_minX;
  double m_maxX;
  double m_maxYaxis;
  Double_t m_binWidth;

  Int_t m_npar;
  Double_t m_fitpars[6];
  Double_t m_fitparsErr[6];
  Double_t m_fitparsUpErr[6];
  Double_t m_fitparsDownErr[6];
  double m_inputSigma;
  int m_nSigma;
  double m_lowRange;
  double m_topRange;

  std::string m_composite;
  std::string m_signal;
  std::string m_bkg;

  TF1* m_compositeFunction;

  TF1* m_signalFunction;
  TF1* m_backgroundFunction;

  TF1* m_compositeFunctionUpErr;
  TF1* m_backgroundFunctionUpErr;

  TF1* m_compositeFunctionDownErr;
  TF1* m_backgroundFunctionDownErr;

  TCanvas* m_canvas;
  TString m_name;
  TH1* m_inputHist;
  TH1* m_inputHist_orig;

  double m_compositeFuncIntegral;
  double m_bkgIntegral;
  double m_sigIntegral;
  double m_sigIntegral_Implied;

  double m_compositeFuncIntegralUpErr;
  double m_bkgIntegralUpErr;
  double m_sigIntegralUpErr_Implied;

  double m_compositeFuncIntegralDownErr;
  double m_bkgIntegralDownErr;
  double m_sigIntegralDownErr_Implied;

  double m_signalMass;

  double m_signalFitMin;
  double m_signalFitMax;
  double m_bkgFitMin;
  double m_bkgFitMax;

 public:
  SingleGausFit(TString name);
  virtual ~SingleGausFit();
  FitResults* fit_InDet(TH1F* inputHist, int Nsigma, TString output);
  FitResults* fit_MuonProbe(TH1F* inputHist, int Nsigma, TString output, double inputSigma);
  FitResults* fit_MatchChi2(TH1F* inputHist, int Nsigma, TString output, double inputSigma);

  ClassDef(SingleGausFit,1)
 };
#endif /* SINGLEGAUSFIT_H_ */
