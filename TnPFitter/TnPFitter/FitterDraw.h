#ifndef TNPFITTER_FITTERDRAW_H_
#define TNPFITTER_FITTERDRAW_H_ 1

// predeclaration
class TCanvas;
class TF1;
class TH1F;
class TLine;
class TFile;

#include "TObject.h"

// RC packages
#include "TnPFitter/FitInterface.h"
#include "JacobUtils/LoggingUtility.h"

// C++
#include <string>

class FitterDraw
{

public:
  struct LineAttrib
  {
    std::string name;
    int color;
    int style;
    float width;
    int npx;
  };

public:
  FitterDraw(FitInterface* fitter = NULL, int sigma = 3, int window = 2);
  
public:
  ~FitterDraw(void);

public:
  void SetupLines(const std::string& options="");
  void SetupLine(TF1* line, LineAttrib* attribute);
  void Draw(const std::string& options="");

private:
  // Fitter
  FitInterface* fFitter; 
  int fSigma;
  int fWindow;

  // Sizes
  float histMin;
  float histMax;

  // Colors and widths
  TFile* configFile;
  LineAttrib* bkgUp;
  LineAttrib* bkgDown;
  LineAttrib* nominal;
  LineAttrib* signal;
  LineAttrib* bkg;

  // Lines
  TLine* fiveLow;
  TLine* fiveHigh;
  TLine* threeLow;
  TLine* threeHigh;
  
  ClassDef(FitterDraw, 1)
};

#endif
