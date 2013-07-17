#ifndef GRAPHER_TOOLS_SCALE_FACTOR_H_
#define GRAPHER_TOOLS_SCALE_FACTOR_H_ 1

#include "TCanvas.h"
#include "TH1F.h"
#include "THStack.h"
#include "TLegend.h"
#include "TPad.h"

namespace GT
{

class ScaleFactor
{

ClassDef(ScaleFactor, 1);

private:
  // Histogram Coloring
  TH1* histo1;

  TH1* histo2;

  
  // Canvas 
  TCanvas* canvas;

  // Pads
  TPad* padTopLeft;
  TPad* padBottomRight;

  // Stack
  THStack* stack;
  
  // SF 
  TH1* SF;

public:
  std::string histo1Title; Style_t markerStyleOne; Color_t colorOne;
  std::string histo2Title; Style_t markerStyleTwo; Color_t colorTwo;
  int doLog;
  
private:
  // SF Attributes
  std::string sfTitle;
  std::string xAxisTitle;
  std::string yAxisTitle;
  const float sfTitleSize;
  const float sfTitleOffset;
  const int sfMarkerStyle;
  const int sfMarkerColor;
  float sfRangeMin;
  float sfRangeMax;


public:
  // Create a new Scale Factor object
  ScaleFactor( const std::string& name,  TH1* h1,  TH1* h2);

public:
  void SetXaxisTitle(const std::string& title);
  void SetYaxisTitle(const std::string& title);
  void SetSFaxisTitle(const std::string& title);

public:
  // Sets the range for the scale factor plot
  void SetSFRange(const float min, const float max);

public:
  void Draw(void);

  void SaveAs(const std::string& path, const std::string& format);

public:
  // Ctor
  ~ScaleFactor();
};

} // End Namespace GT

#endif
// END GRAPHER_TOOLS_SCALE_FACTOR_H_
