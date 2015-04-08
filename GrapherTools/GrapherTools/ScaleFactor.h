#ifndef GRAPHER_TOOLS_SCALE_FACTOR_H_
#define GRAPHER_TOOLS_SCALE_FACTOR_H_ 1

#include "GrapherTools/ScaleFactorComponent.h"
#include "GrapherTools/ScaleFactorAttributes.h"

#include <string>

#include "TCanvas.h"
#include "THStack.h"
#include "TH1F.h"
#include "TLegend.h"

namespace GT {

class ScaleFactor {
 public:
  ScaleFactor(SFAttributes attributes,
              SFComponent numerator,
              SFComponent denominator);
  ~ScaleFactor() = default;

 public:
  void Draw(void);
  void SaveAs(std::string path, std::string format);

 private:
  void addComponentToStack(SFComponent component);
  void enableMiddleTicks(TCanvas& canvas);
  void drawStack();
  void setupScaleFactorHistogram();

 public:
  SFAttributes attributes;
  SFComponent numerator;
  SFComponent denominator;

 private:
  TCanvas canvas;
  THStack stack;
  TLegend leg;
  TH1F SF;

#ifdef __CINT__
  ClassDef(ScaleFactor, 1);
#endif
};
}
#endif
