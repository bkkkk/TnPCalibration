#ifndef GRAPHER_TOOLS_SCALE_FACTOR_H_
#define GRAPHER_TOOLS_SCALE_FACTOR_H_ 1

#include "TCanvas.h"
#include "TH1F.h"
#include "THStack.h"
#include "TLegend.h"
#include "TPad.h"

namespace GT
{

struct SFAttributes {
  SFAttributes() {
  }

  std::string Title;
  std::string xAxisTitle;
  std::string yAxisTitle;
  const float titleSize;
  const float titleOffset;
  const int markerStyle;
  const int markerColor;
  float minimum;
  float maximum;
};

struct SFComponent {
  SFComponent(std::unique_ptr<TH1> histogram, const std::string& title, Style_t markerStyle, Color_t color) : histogram(std::move(histogram)), title(title), markerStyle(markerStyle), color(color) {}

  std::unique_ptr<TH1> histogram;
  std::string title;
  Style_t markerStyle;
  Color_t color;
};

class ScaleFactor {  

ClassDef(ScaleFactor, 1);

private:
  TCanvas canvas;
  TPad padTopLeft;
  TPad padBottomRight;
  THStack stack;
  TH1* SF;

public:
  SFComponent numerator;
  SFComponent denominator;
  SFAttributes attributes;

public:
  ScaleFactor(const std::string& name, const SFComponent& numerator, const SFComponent& denominator);

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
