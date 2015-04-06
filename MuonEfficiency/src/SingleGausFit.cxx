/*
 * SingleGausFit.cpp
 *
 *  Created on: 24 Oct 2011
 *      Author: coopers
 */

#include "MuonEfficiency/SingleGausFit.h"
#include "TMath.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TObject.h"
#include "TH1.h"
#include "TLine.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "JacobUtils/LoggingUtility.h"

#include <limits>

ClassImp(SingleGausFit)

SingleGausFit::SingleGausFit(TString name) {
  // TODO Auto-generated constructor stub
  m_minX = 2.6;
  m_maxX = 3.6;
  m_maxYaxis = 0.0;
  m_binWidth = -1;
  m_npar = 6;
  m_fitpars[0] = 0.;
  m_fitpars[1] = 0.;
  m_fitpars[2] = 0.;
  m_fitpars[3] = 0.;
  m_fitpars[4] = 0.;
  m_fitpars[5] = 0.;
  m_nSigma = 0;
  m_lowRange = 0;
  m_topRange = 0;
  m_compositeFunction = NULL;
  m_signalFunction = NULL;
  m_backgroundFunction = NULL;
  m_compositeFunctionUpErr = NULL;
  m_backgroundFunctionUpErr = NULL;
  m_compositeFunctionDownErr = NULL;
  m_backgroundFunctionDownErr = NULL;
  m_name = name;
  m_inputHist = NULL;
  m_inputHist_orig = NULL;
  m_bkgIntegral = 0.;
  m_sigIntegral = 0.;
  m_sigIntegral_Implied = 0.;
  m_compositeFuncIntegralUpErr = 0.;
  m_bkgIntegralUpErr = 0.;
  m_sigIntegralUpErr_Implied = 0.;
  m_compositeFuncIntegralDownErr = 0.;
  m_bkgIntegralDownErr = 0.;
  m_sigIntegralDownErr_Implied = 0.;
  m_composite = "[0] + [1]*x + [2] * x * x + gaus(3)";
  m_signal = "gaus(0)";
  m_bkg = "[0] + [1]*x + [2] * x * x";
  m_signalMass = 3.097;
  m_signalFitMin = 2.8;
  m_signalFitMax = 3.4;
}

SingleGausFit::~SingleGausFit() {
  m_canvas = NULL;
  m_inputHist = NULL;
  m_inputHist_orig = NULL;
  delete m_compositeFunction;
  delete m_signalFunction;
  delete m_backgroundFunction;
  delete m_compositeFunctionUpErr;
  delete m_backgroundFunctionUpErr;
  delete m_compositeFunctionDownErr;
  delete m_backgroundFunctionDownErr;
}

void SingleGausFit::setCompositeFitFunc(){

    LOG_DEBUG2() << "|----------------------------------------------------------------|";
    LOG_DEBUG2() << "| Performing composite fit ....";
    m_canvas->cd();

    // Fit function
    m_compositeFunction = new TF1("myfit", m_composite.c_str(), m_minX, m_maxX);
    m_compositeFunction->SetLineColor(4);
    m_compositeFunction->SetLineWidth(2.5);


    //m_compositeFunction->SetParameters(m_fitpars);
    m_compositeFunction->SetParNames("Constant", "Slope", "PolyFunc", "N", "m", "#sigma");
    m_compositeFunction->SetParameter(3, m_inputHist->GetMaximum());
    m_compositeFunction->SetParameter(4, 3.097);
    m_compositeFunction->SetParLimits(4, m_signalFitMin, m_signalFitMax);
    m_compositeFunction->SetParLimits(5, 0.01, 0.2);

    LOG_DEBUG2() << "|-> Using the following parameters: ";
    LOG_DEBUG2() << "|-->  Constant = " << m_compositeFunction->GetParameter(0) << ", Limits (Low,High) = No Limit";
    LOG_DEBUG2() << "|-->  Slope = " << m_compositeFunction->GetParameter(1) << ", Limits (Low,High) = No Limit";
    LOG_DEBUG2() << "|-->  PolyFunc = " << m_compositeFunction->GetParameter(2) << ", Limits (Low,High) = No Limit";
    LOG_DEBUG2() << "|-->  N = " << m_compositeFunction->GetParameter(3) << ", Limits (Low,High) = No Limit";
    LOG_DEBUG2() << "|-->  Mass (mu) = " << m_compositeFunction->GetParameter(4) << ", Limits (Low,High) = " << m_signalFitMin << "," << m_signalFitMax;
    LOG_DEBUG2() << "|-->  Sigma = " << m_compositeFunction->GetParameter(5) << ", Limits (Low,High) = " << 0.001 << "," << 0.2;
    LOG_DEBUG2() << "|-> Fitting between " << m_minX << ", " << m_maxX;


    // Do the fit
    m_inputHist->Fit("myfit","MERBS");
    m_compositeFunction->GetParameters(m_fitpars);

    // Set the errors of the fit
    m_fitparsErr[0] = m_compositeFunction->GetParError(0);
    m_fitparsErr[1] = m_compositeFunction->GetParError(1);
    m_fitparsErr[2] = m_compositeFunction->GetParError(2);
    m_fitparsErr[3] = m_compositeFunction->GetParError(3);
    m_fitparsErr[4] = m_compositeFunction->GetParError(4);
    m_fitparsErr[5] = m_compositeFunction->GetParError(5);

    LOG_DEBUG2() << "|-> Fit has been performed. Results: ";
    LOG_DEBUG2() << "|-->  Constant = " << m_fitpars[0] << " +/- " << m_fitparsErr[0];
    LOG_DEBUG2() << "|-->  Slope = " << m_fitpars[1] << " +/- " << m_fitparsErr[1];
    LOG_DEBUG2() << "|-->  PolyFunc = " << m_fitpars[2] << " +/- " << m_fitparsErr[2];
    LOG_DEBUG2() << "|-->  N = " << m_fitpars[3] << " +/- " << m_fitparsErr[3];
    LOG_DEBUG2() << "|-->  Mass (mu) = " << m_fitpars[4] << " +/- " << m_fitparsErr[4];
    LOG_DEBUG2() << "|-->  Sigma = " << m_fitpars[5] << " +/- " << m_fitparsErr[5];

    // Set histogram attributes
    m_inputHist->GetXaxis()->SetRangeUser(2.2,3.8);
    m_inputHist->GetYaxis()->SetRangeUser(0,1.2*(m_inputHist->GetMaximum()));
    m_inputHist->SetTitle("");
    m_inputHist->GetXaxis()->SetTitle("M (#mu+,#mu-) [GeV]");
    m_maxYaxis = (m_inputHist->GetMaximum());
    m_binWidth = m_inputHist->GetBinWidth(1);

    // Now draw the fit on the same plot
    m_compositeFunction->Draw("SAME");

    LOG_DEBUG2() << "| Composite fit done ....";
    LOG_DEBUG2() << "|----------------------------------------------------------------|";

}

void SingleGausFit::setCompositeFitFunc(double inputSigma){

    LOG_DEBUG2() << "|----------------------------------------------------------------|";
    LOG_DEBUG2() << "| Performing composite fit ....";
    m_canvas->cd();

    // Fit function
    m_compositeFunction = new TF1("myfit", m_composite.c_str(), m_minX, m_maxX);
    m_compositeFunction->SetLineColor(4);
    m_compositeFunction->SetLineWidth(2.5);


    //m_compositeFunction->SetParameters(m_fitpars);
    m_compositeFunction->SetParNames("Constant","Slope","PolyFunc","N","m","#sigma");
    m_compositeFunction->SetParameter(3,m_inputHist->GetMaximum());
    m_compositeFunction->SetParameter(4, m_signalMass);
    m_compositeFunction->SetParLimits(4, m_signalFitMin, m_signalFitMax);
    m_compositeFunction->SetParameter(5, inputSigma);
    m_compositeFunction->SetParLimits(5, 0.01, 0.2);

    LOG_DEBUG2() << "|-> Using the following parameters: ";
    LOG_DEBUG2() << "|-->  Constant = " << m_compositeFunction->GetParameter(0) << ", Limits (Low,High) = No Limit";
    LOG_DEBUG2() << "|-->  Slope = " << m_compositeFunction->GetParameter(1) << ", Limits (Low,High) = No Limit";
    LOG_DEBUG2() << "|-->  PolyFunc = " << m_compositeFunction->GetParameter(2) << ", Limits (Low,High) = No Limit";
    LOG_DEBUG2() << "|-->  N = " << m_compositeFunction->GetParameter(3) << ", Limits (Low,High) = No Limit";
    LOG_DEBUG2() << "|-->  Mass (mu) = " << m_compositeFunction->GetParameter(4) << ", Limits (Low,High) = " << m_signalFitMin << "," << m_signalFitMax;
    LOG_DEBUG2() << "|-->  Sigma = " << m_compositeFunction->GetParameter(5) << ", Limits (Low,High) = " << 0.001 << "," << 0.2;
    LOG_DEBUG2() << "|-> Fitting between " << m_minX << ", " << m_maxX;


    // Do the fit
    m_inputHist->Fit("myfit","MERB");
    m_compositeFunction->GetParameters(m_fitpars);

    // Set the errors of the fit
    m_fitparsErr[0] = m_compositeFunction->GetParError(0);
    m_fitparsErr[1] = m_compositeFunction->GetParError(1);
    m_fitparsErr[2] = m_compositeFunction->GetParError(2);
    m_fitparsErr[3] = m_compositeFunction->GetParError(3);
    m_fitparsErr[4] = m_compositeFunction->GetParError(4);
    m_fitparsErr[5] = m_compositeFunction->GetParError(5);

    LOG_DEBUG2() << "|-> Fit has been performed. Results: ";
    LOG_DEBUG2() << "|-->  Constant = " << m_fitpars[0] << " +/- " << m_fitparsErr[0];
    LOG_DEBUG2() << "|-->  Slope = " << m_fitpars[1] << " +/- " << m_fitparsErr[1];
    LOG_DEBUG2() << "|-->  PolyFunc = " << m_fitpars[2] << " +/- " << m_fitparsErr[2];
    LOG_DEBUG2() << "|-->  N = " << m_fitpars[3] << " +/- " << m_fitparsErr[3];
    LOG_DEBUG2() << "|-->  Mass (mu) = " << m_fitpars[4] << " +/- " << m_fitparsErr[4];
    LOG_DEBUG2() << "|-->  Sigma = " << m_fitpars[5] << " +/- " << m_fitparsErr[5];

    // Set histogram attributes
    m_inputHist->GetXaxis()->SetRangeUser(2.2,3.8);
    m_inputHist->GetYaxis()->SetRangeUser(0,1.2*(m_inputHist->GetMaximum()));
    m_inputHist->SetTitle("");
    m_inputHist->GetXaxis()->SetTitle("M (#mu+,#mu-) [GeV]");
    m_maxYaxis = (m_inputHist->GetMaximum());
    m_binWidth = m_inputHist->GetBinWidth(1);

    // Now draw the fit on the same plot
    m_compositeFunction->Draw("SAME");

    LOG_DEBUG2() << "| Composite fit done ....";
    LOG_DEBUG2() << "|----------------------------------------------------------------|";

}

void SingleGausFit::setBackgroundFitFunc(){

    LOG_DEBUG2() << "|----------------------------------------------------------------|";
    LOG_DEBUG2() << "| Extracting background profile from composite function ....";

    LOG_DEBUG2() << "|-> Creating function between " << m_minX << ", " << m_maxX;

    m_backgroundFunction = new TF1("backg", m_bkg.c_str(), m_minX, m_maxX);
    m_backgroundFunction->SetParameters(m_fitpars);
    m_backgroundFunction->SetLineStyle(5);
    m_backgroundFunction->Draw("SAME");

    LOG_DEBUG2() << "|-> Background function = " << m_fitpars[0] << " + " << m_fitpars[1] << "x" << " + " << m_fitpars[2] << "x^2";

    LOG_DEBUG2() << "| Background extraction done ....";
    LOG_DEBUG2() << "|----------------------------------------------------------------|";

}

void SingleGausFit::setSignalFitFunc(){

    LOG_DEBUG2() << "|----------------------------------------------------------------|";
    LOG_DEBUG2() << "| Extracting signal profile from composite function ....";

    LOG_DEBUG2() << "|-> Creating function between " << m_minX << ", " << m_maxX;

    m_signalFunction = new TF1("signalFcn", m_signal.c_str(), 2.8, 3.4);
    m_signalFunction->SetParameter(0, m_fitpars[3]);
    m_signalFunction->SetParameter(1, m_fitpars[4]);
    m_signalFunction->SetParLimits(1, m_signalFitMin, m_signalFitMax);
    m_signalFunction->SetParameter(2, m_fitpars[5]);
    m_signalFunction->SetLineColor(2);
    m_signalFunction->Draw("SAME");

    LOG_DEBUG2() << "|-> Signal function = " << m_fitpars[3] << " e-0.5( (x - " << m_fitpars[4] << ")/" << m_fitpars[5] << " )^2";

    LOG_DEBUG2() << "| Signal extraction done ....";
    LOG_DEBUG2() << "|----------------------------------------------------------------|";
}

void SingleGausFit::setSigmaRanges(){

    LOG_DEBUG2() << "|----------------------------------------------------------------|";
    LOG_DEBUG2() << "| Setting the sigma ranges up ....";

    Double_t sigma = m_fitpars[5];
    Double_t nSigma = m_nSigma * sigma;
    m_lowRange = 3.097 - nSigma;
    m_topRange = 3.097 + nSigma;

    LOG_DEBUG2() << "|-> Sigma Ranges:";
    LOG_DEBUG2() << "|--> Sigma = " << sigma;
    LOG_DEBUG2() << "|--> " << m_nSigma << " Sigma = " << nSigma;
    LOG_DEBUG2() << "|--> Low Range = " << m_lowRange;
    LOG_DEBUG2() << "|--> High Range = " << m_topRange;
    LOG_DEBUG2() << "|--> Bin Width = " << m_binWidth;

    Double_t lowRange3 = 3.097 - ( 3 * sigma );
    Double_t topRange3 = 3.097 + ( 3 * sigma );
    Double_t lowRange5 = 3.097 - ( 5 * sigma );
    Double_t topRange5 = 3.097 + ( 5 * sigma );

    LOG_DEBUG2() << "|-> Drawing 3 sigma lines on plot";
    TLine *minSigma3 = new TLine(lowRange3,0.0,lowRange3,m_maxYaxis);
    minSigma3->SetLineColor(6);
    minSigma3->SetLineWidth(2);
    minSigma3->Draw();
    TLine *maxSigma3 = new TLine(topRange3,0.0,topRange3,m_maxYaxis);
    maxSigma3->SetLineColor(6);
    maxSigma3->SetLineWidth(2);
    maxSigma3->Draw();

    LOG_DEBUG2() << "|-> Drawing 5 sigma lines on plot";
    TLine *minSigma5 = new TLine(lowRange5,0.0,lowRange5,m_maxYaxis);
    minSigma5->SetLineColor(3);
    minSigma5->SetLineWidth(2);
    minSigma5->Draw();
    TLine *maxSigma5 = new TLine(topRange5,0.0,topRange5,m_maxYaxis);
    maxSigma5->SetLineColor(3);
    maxSigma5->SetLineWidth(2);
    maxSigma5->Draw();


    LOG_DEBUG2() << "| Sigma ranges done ....";
    LOG_DEBUG2() << "|----------------------------------------------------------------|";
}

void SingleGausFit::setSigmaRanges(double inputSigma){

    LOG_DEBUG2() << "|----------------------------------------------------------------|";
    LOG_DEBUG2() << "| Setting the sigma ranges up ....";

    Double_t sigma      = inputSigma;
    Double_t nSigma     = m_nSigma*sigma;
    m_lowRange   = 3.097-nSigma;
    m_topRange   = 3.097+nSigma;

    LOG_DEBUG2() << "|-> Sigma Ranges:";
    LOG_DEBUG2() << "|--> Sigma = " << sigma;
    LOG_DEBUG2() << "|--> " << m_nSigma << " Sigma = " << nSigma;
    LOG_DEBUG2() << "|--> Low Range = " << m_lowRange;
    LOG_DEBUG2() << "|--> High Range = " << m_topRange;
    LOG_DEBUG2() << "|--> Bin Width = " << m_binWidth;

    Double_t lowRange3   = 3.097-(3*sigma);
    Double_t topRange3   = 3.097+(3*sigma);
    Double_t lowRange5   = 3.097-(5*sigma);
    Double_t topRange5   = 3.097+(5*sigma);

    LOG_DEBUG2() << "|-> Drawing 3 sigma lines on plot";
    TLine *minSigma3 = new TLine(lowRange3,0.0,lowRange3,m_maxYaxis);
    minSigma3->SetLineColor(6);
    minSigma3->SetLineWidth(2);
    minSigma3->Draw();
    TLine *maxSigma3 = new TLine(topRange3,0.0,topRange3,m_maxYaxis);
    maxSigma3->SetLineColor(6);
    maxSigma3->SetLineWidth(2);
    maxSigma3->Draw();

    LOG_DEBUG2() << "|-> Drawing 5 sigma lines on plot";
    TLine *minSigma5 = new TLine(lowRange5,0.0,lowRange5,m_maxYaxis);
    minSigma5->SetLineColor(3);
    minSigma5->SetLineWidth(2);
    minSigma5->Draw();
    TLine *maxSigma5 = new TLine(topRange5,0.0,topRange5,m_maxYaxis);
    maxSigma5->SetLineColor(3);
    maxSigma5->SetLineWidth(2);
    maxSigma5->Draw();


    LOG_DEBUG2() << "| Sigma ranges done ....";
    LOG_DEBUG2() << "|----------------------------------------------------------------|";
}

void SingleGausFit::setCompositeFitFuncUpErr(){

    LOG_DEBUG2() << "|----------------------------------------------------------------|";
    LOG_DEBUG2() << "| Performing composite fit Up Error ....";

    m_compositeFunctionUpErr = new TF1("UppErr", m_composite.c_str(), m_minX, m_maxX);
    m_compositeFunctionUpErr->SetParameters(m_fitpars);
    m_compositeFunctionUpErr->SetParNames("Constant","Slope","PolyFunc","N","m","#sigma");
    m_compositeFunctionUpErr->FixParameter(0, m_fitpars[0]+m_fitparsErr[0]);
    m_compositeFunctionUpErr->FixParameter(1, m_fitpars[1]-m_fitparsErr[1]);
    m_compositeFunctionUpErr->FixParameter(2, m_fitpars[2]+m_fitparsErr[2]);
    m_compositeFunctionUpErr->SetParameter(3, m_inputHist->GetMaximum());
    m_compositeFunctionUpErr->SetParameter(4, m_signalMass);
    m_compositeFunctionUpErr->SetParLimits(4, m_signalFitMin, m_signalFitMax);
    m_compositeFunctionUpErr->SetParLimits(5, 0.01, 0.2);

    m_compositeFunctionUpErr->GetParameters(m_fitparsUpErr);

    LOG_DEBUG2() << "Using the following parameters: ";
    LOG_DEBUG2() << "Constant = " << m_fitparsUpErr[0];
    LOG_DEBUG2() << "Slope = " << m_fitparsUpErr[1];
    LOG_DEBUG2() << "PolyFunc = " << m_fitparsUpErr[2];
    LOG_DEBUG2() << "N = " << m_fitparsUpErr[3];
    LOG_DEBUG2() << "Mass (mu) = " << m_fitparsUpErr[4];
    LOG_DEBUG2() << "Sigma = " << m_fitparsUpErr[5];
    LOG_DEBUG2() << "Fitting between " << m_minX << ", " << m_maxX;

    m_inputHist->Fit("UppErr","MQRN");
    m_compositeFunctionUpErr->GetParameters(m_fitparsUpErr);

    LOG_DEBUG2() << "|-> Fit has been performed. Results: ";
    LOG_DEBUG2() << "|-->  Constant = " << m_fitparsUpErr[0];
    LOG_DEBUG2() << "|-->  Slope = " << m_fitparsUpErr[1];
    LOG_DEBUG2() << "|-->  PolyFunc = " << m_fitparsUpErr[2];
    LOG_DEBUG2() << "|-->  N = " << m_fitparsUpErr[3];
    LOG_DEBUG2() << "|-->  Mass (mu) = " << m_fitparsUpErr[4];
    LOG_DEBUG2() << "|-->  Sigma = " << m_fitparsUpErr[5];

    m_compositeFunctionUpErr->SetLineColor(9);
    m_compositeFunctionUpErr->SetLineStyle(2);
    m_compositeFunctionUpErr->Draw("SAME");

    LOG_DEBUG2() << "| Done composite fit Up Error ....";
    LOG_DEBUG2() << "|----------------------------------------------------------------|";
}

void SingleGausFit::setBackgroundFitFuncUpErr(){

    LOG_DEBUG2() << "|----------------------------------------------------------------|";
    LOG_DEBUG2() << "| Performing background fit Up Error ....";

    m_backgroundFunctionUpErr = new TF1("Upp_backg", m_bkg.c_str(), m_minX, m_maxX);
    m_backgroundFunctionUpErr->SetParameters(m_fitparsUpErr);

    m_backgroundFunctionUpErr->SetLineColor(9);
    m_backgroundFunctionUpErr->SetLineStyle(2);
    m_backgroundFunctionUpErr->Draw("SAME");

    LOG_DEBUG2() << "|-> Background function = " << m_fitparsUpErr[0] << "x + " << m_fitparsUpErr[1] << " + " << m_fitparsUpErr[2] << "x^2";

    LOG_DEBUG2() << "| Done background fit Up Error ....";
    LOG_DEBUG2() << "|----------------------------------------------------------------|";
}

void SingleGausFit::setCompositeFitFuncDownErr(){

    LOG_DEBUG2() << "|----------------------------------------------------------------|";
    LOG_DEBUG2() << "| Performing composite fit Down Error ....";

    m_compositeFunctionDownErr = new TF1("DownErr", m_composite.c_str(), m_minX, m_maxX);
    m_compositeFunctionDownErr->SetParameters(m_fitpars);
    m_compositeFunctionDownErr->SetParNames("Constant","Slope","PolyFunc","N","m","#sigma");
    m_compositeFunctionDownErr->FixParameter(0, m_fitpars[0]-m_fitparsErr[0]);
    m_compositeFunctionDownErr->FixParameter(1, m_fitpars[1]+m_fitparsErr[1]);
    m_compositeFunctionDownErr->FixParameter(2, m_fitpars[2]-m_fitparsErr[2]);
    m_compositeFunctionDownErr->SetParameter(3, m_inputHist->GetMaximum());
    m_compositeFunctionDownErr->SetParameter(4, m_signalMass);
    m_compositeFunctionDownErr->SetParLimits(4, m_signalFitMin, m_signalFitMax);
    m_compositeFunctionDownErr->SetParLimits(5, 0.01, 0.2);

    m_compositeFunctionDownErr->GetParameters(m_fitparsDownErr);

    LOG_DEBUG2() << "|-> Using the following parameters: ";
    LOG_DEBUG2() << "|-->  Constant = " << m_fitparsDownErr[0];
    LOG_DEBUG2() << "|-->  Slope = " << m_fitparsDownErr[1];
    LOG_DEBUG2() << "|-->  PolyFunc = " << m_fitparsDownErr[2];
    LOG_DEBUG2() << "|-->  N = " << m_fitparsDownErr[3];
    LOG_DEBUG2() << "|-->  Mass (mu) = " << m_fitparsDownErr[4];
    LOG_DEBUG2() << "|-->  Sigma = " << m_fitparsDownErr[5];
    LOG_DEBUG2() << "|-> Fitting between " << m_minX << ", " << m_maxX;

    m_inputHist->Fit("DownErr","MQRN");
    m_compositeFunctionDownErr->GetParameters(m_fitparsDownErr);

    LOG_DEBUG2() << "|-> Fit has been performed. Results: ";
    LOG_DEBUG2() << "|-->  Constant = " << m_fitparsDownErr[0];
    LOG_DEBUG2() << "|-->  Slope = " << m_fitparsDownErr[1];
    LOG_DEBUG2() << "|-->  PolyFunc = " << m_fitparsDownErr[2];
    LOG_DEBUG2() << "|-->  N = " << m_fitparsDownErr[3];
    LOG_DEBUG2() << "|-->  Mass (mu) = " << m_fitparsDownErr[4];
    LOG_DEBUG2() << "|-->  Sigma = " << m_fitparsDownErr[5];

    m_compositeFunctionDownErr->SetLineColor(46);
    m_compositeFunctionDownErr->SetLineStyle(2);
    m_compositeFunctionDownErr->Draw("SAME");

    LOG_DEBUG2() << "| Done composite fit Down Error ....";
    LOG_DEBUG2() << "|----------------------------------------------------------------|";
}

void SingleGausFit::setBackgroundFitFuncDownErr(){

    LOG_DEBUG2() << "|----------------------------------------------------------------|";
    LOG_DEBUG2() << "| Performing background fit Down Error ....";

    m_backgroundFunctionDownErr = new TF1("Down_backg", m_bkg.c_str(), m_minX, m_maxX);
    m_backgroundFunctionDownErr->SetParameters(m_fitparsDownErr);

    m_backgroundFunctionDownErr->SetLineColor(46);
    m_backgroundFunctionDownErr->SetLineStyle(2);
    m_backgroundFunctionDownErr->Draw("SAME");

    LOG_DEBUG2() << "|-> Background function = " << m_fitparsDownErr[0] << " + " << m_fitparsDownErr[1] << "x + " << m_fitparsDownErr[2] << "x^2";

    LOG_DEBUG2() << "| Done background fit Down Error ....";
    LOG_DEBUG2() << "|----------------------------------------------------------------|";
}

void SingleGausFit::setIntegrals(){

    LOG_DEBUG2() << "|----------------------------------------------------------------|";
    LOG_DEBUG2() << "| Calculating the integrals ....";

    m_compositeFuncIntegral = (m_compositeFunction->Integral(m_lowRange,m_topRange))/m_binWidth;
    m_bkgIntegral = (m_backgroundFunction->Integral(m_lowRange,m_topRange))/m_binWidth;
    m_sigIntegral = (m_signalFunction->Integral(m_lowRange,m_topRange))/m_binWidth;
    m_sigIntegral_Implied = m_compositeFuncIntegral - m_bkgIntegral;

    m_compositeFuncIntegralUpErr = (m_compositeFunctionUpErr->Integral(m_lowRange,m_topRange))/m_binWidth;
    m_bkgIntegralUpErr = (m_backgroundFunctionUpErr->Integral(m_lowRange,m_topRange))/m_binWidth;
    m_sigIntegralUpErr_Implied = m_compositeFuncIntegralUpErr - m_bkgIntegralUpErr;

    m_compositeFuncIntegralDownErr = (m_compositeFunctionDownErr->Integral(m_lowRange,m_topRange))/m_binWidth;
    m_bkgIntegralDownErr = (m_backgroundFunctionDownErr->Integral(m_lowRange,m_topRange))/m_binWidth;
    m_sigIntegralDownErr_Implied = m_compositeFuncIntegralDownErr - m_bkgIntegralDownErr;

    LOG_DEBUG2() << "|--> Integrals:";
    LOG_DEBUG2() << "|--> Composite Fit integral = " << m_compositeFuncIntegral
       << ", Max = " << m_compositeFuncIntegralUpErr
       << ", Min = " << m_compositeFuncIntegralDownErr
      ;
    LOG_DEBUG2() << "|--> Background Fit integral = " << m_bkgIntegral
       << ", Max = " << m_bkgIntegralUpErr
       << ", Min = " << m_bkgIntegralDownErr
      ;
    LOG_DEBUG2() << "|--> Implied Signal integral = " << m_sigIntegral_Implied
       << ", Max = " << m_sigIntegralUpErr_Implied
       << ", Min = " << m_sigIntegralDownErr_Implied
      ;

    if (m_sigIntegralUpErr_Implied < m_sigIntegral_Implied || m_sigIntegralDownErr_Implied > m_sigIntegral_Implied){
      LOG_DEBUG2() << "### Warning";
    }


    LOG_DEBUG2() << "| integrals done ....";
    LOG_DEBUG2() << "|----------------------------------------------------------------|";
}

FitResults* SingleGausFit::fit_InDet(TH1F* inputHist, int Nsigma, TString output)
{
 // 1.- fit the mass histogram
 // 2.- extract the ratio of signal to bkgd in signal window

  // Set the inputs up.
  m_inputHist_orig = inputHist;
  m_inputHist_orig->Sumw2();
  m_inputHist = (TH1F*)m_inputHist_orig->Clone();
  m_nSigma = Nsigma;

  m_canvas = new TCanvas(m_name+"InDet",m_name+"InDet",600,0,800,700);


  this->setCompositeFitFunc();

  this->setBackgroundFitFunc();

  this->setSignalFitFunc();

  this->setSigmaRanges();

  this->setCompositeFitFuncUpErr();
  this->setBackgroundFitFuncUpErr();

  this->setCompositeFitFuncDownErr();
  this->setBackgroundFitFuncDownErr();

  this->setIntegrals();

  m_canvas->Print(output);
  m_canvas->Write();
  m_canvas->Clear();
  m_canvas->Close();

  FitResults* returnFitResult = new FitResults(m_fitpars,
                        m_fitparsErr,
                        m_fitparsUpErr,
                        m_fitparsDownErr,
                        m_compositeFuncIntegral,
                        m_bkgIntegral,
                        m_sigIntegral_Implied,
                        m_compositeFuncIntegralUpErr,
                        m_bkgIntegralUpErr,
                        m_sigIntegralUpErr_Implied,
                        m_compositeFuncIntegralDownErr,
                        m_bkgIntegralDownErr,
                        m_sigIntegralDownErr_Implied);


  delete m_compositeFunction;
  delete m_signalFunction;
  delete m_backgroundFunction;
  delete m_compositeFunctionUpErr;
  delete m_backgroundFunctionUpErr;
  delete m_compositeFunctionDownErr;
  delete m_backgroundFunctionDownErr;

  return returnFitResult;

}

FitResults* SingleGausFit::fit_MuonProbe(TH1F* inputHist, int Nsigma, TString output, double inputSigma)
{
 // 1.- fit the mass histogram
 // 2.- extract the ratio of signal to bkgd in signal window

  // Set the inputs up.
  m_inputHist_orig = inputHist;
  m_inputHist_orig->Sumw2();
  m_inputHist = (TH1F*)m_inputHist_orig->Clone();
  m_nSigma = Nsigma;

  m_canvas = new TCanvas(m_name+"MuonProbe",m_name+"MuonProbe",600,0,800,700);

  this->setCompositeFitFunc(inputSigma);

  this->setBackgroundFitFunc();

  this->setSignalFitFunc();

  this->setSigmaRanges(inputSigma);

  this->setCompositeFitFuncUpErr();
  this->setBackgroundFitFuncUpErr();

  this->setCompositeFitFuncDownErr();
  this->setBackgroundFitFuncDownErr();

  this->setIntegrals();

  m_canvas->Print(output);
  m_canvas->Write();
  m_canvas->Clear();
  m_canvas->Close();

  FitResults* returnFitResultMp = new FitResults(m_fitpars,
                        m_fitparsErr,
                        m_fitparsUpErr,
                        m_fitparsDownErr,
                        m_compositeFuncIntegral,
                        m_bkgIntegral,
                        m_sigIntegral_Implied,
                        m_compositeFuncIntegralUpErr,
                        m_bkgIntegralUpErr,
                        m_sigIntegralUpErr_Implied,
                        m_compositeFuncIntegralDownErr,
                        m_bkgIntegralDownErr,
                        m_sigIntegralDownErr_Implied);

  delete m_compositeFunction;
  delete m_signalFunction;
  delete m_backgroundFunction;
  delete m_compositeFunctionUpErr;
  delete m_backgroundFunctionUpErr;
  delete m_compositeFunctionDownErr;
  delete m_backgroundFunctionDownErr;

  return returnFitResultMp;

}

FitResults* SingleGausFit::fit_MatchChi2(TH1F* inputHist, int Nsigma, TString output, double inputSigma)
{

 // 1.- fit the mass histogram
 // 2.- extract the ratio of signal to bkgd in signal window

  // Set the inputs up.
  m_inputHist_orig = inputHist;
  m_inputHist_orig->Sumw2();
  m_inputHist = (TH1F*)m_inputHist_orig->Clone();
  m_nSigma = Nsigma;

  m_canvas = new TCanvas(m_name+"MatchChi2",m_name+"MatchChi2",600,0,800,700);

  this->setCompositeFitFunc(inputSigma);

  this->setBackgroundFitFunc();

  this->setSignalFitFunc();

  this->setSigmaRanges(inputSigma);

  this->setCompositeFitFuncUpErr();
  this->setBackgroundFitFuncUpErr();

  this->setCompositeFitFuncDownErr();
  this->setBackgroundFitFuncDownErr();

  this->setIntegrals();

  m_canvas->Print(output);
  m_canvas->Write();
  m_canvas->Clear();
  m_canvas->Close();

  FitResults* returnFitResultMChi2 = new FitResults(m_fitpars,
                        m_fitparsErr,
                        m_fitparsUpErr,
                        m_fitparsDownErr,
                        m_compositeFuncIntegral,
                        m_bkgIntegral,
                        m_sigIntegral_Implied,
                        m_compositeFuncIntegralUpErr,
                        m_bkgIntegralUpErr,
                        m_sigIntegralUpErr_Implied,
                        m_compositeFuncIntegralDownErr,
                        m_bkgIntegralDownErr,
                        m_sigIntegralDownErr_Implied);

  delete m_compositeFunction;
  delete m_signalFunction;
  delete m_backgroundFunction;
  delete m_compositeFunctionUpErr;
  delete m_backgroundFunctionUpErr;
  delete m_compositeFunctionDownErr;
  delete m_backgroundFunctionDownErr;

  return returnFitResultMChi2;
}
