#ifndef TNPFITTER_FITTERDRAW_H_
#define TNPFITTER_FITTERDRAW_H_ 1

class TCanvas;
class TF1;
class TH1F;
class TLine;
class TFile;
class TPaveText;

#include "TObject.h"

#include "TnPFitter/FitInterface.h"
#include "JacobUtils/LoggingUtility.h"

#include <string>

class FitterDraw {

public:
  struct LineAttrib {
    std::string name;
    int color;
    int style;
    float width;
    int npx;
  };

public:
  FitterDraw(FitInterface* fitter = nullptr, int sigma = 3, int window = 2);
  ~FitterDraw(void);

public:
  void SetupLines(const std::string& options="");
  void SetupLine(TF1* line, LineAttrib* attribute);
  void SetupBox(void);
  void Draw(const std::string& options="");

private:
  FitInterface* fFitter; 
  int fSigma;
  int fWindow;

  float histMin;
  float histMax;

  TFile* configFile;
  LineAttrib* bkgUp;
  LineAttrib* bkgDown;
  LineAttrib* nominal;
  LineAttrib* signal;
  LineAttrib* bkg;

  TLine* fiveLow;
  TLine* fiveHigh;
  TLine* threeLow;
  TLine* threeHigh;
  
  TPaveText* box;

#ifdef __CINT__
  ClassDef(FitterDraw, 1)
#endif
};

#endif
