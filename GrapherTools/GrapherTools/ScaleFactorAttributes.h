#ifndef SCALEFACTOR_ATTRIBUTES_H_
#define SCALEFACTOR_ATTRIBUTES_H_ 1

#include <string>

class SFAttributes {
 public:
  SFAttributes(std::string title);

 public:
  static SFAttributes constructScaleFactorWithTitle(std::string title);
  SFAttributes& withRange(float min, float max);
  SFAttributes& withTitleSize(float size);
  SFAttributes& withTitleOffset(float offset);
  SFAttributes& withMarkerStyle(unsigned style);
  SFAttributes& withMarkerColor(unsigned color);
  SFAttributes& withXAxisTitle(std::string title);
  SFAttributes& withYAxisTitle(std::string title);

 public:
  std::string getTitle();
  std::string getXAxisTitle();
  std::string getYAxisTitle();
  float getMinimum();
  float getMaximum();
  float getTitleSize() { return (titleSize); }
  float getTitleOffset() { return (titleOffset); }
  unsigned getMarkerStyle() { return (markerStyle); }
  unsigned getMarkerColor() { return (markerColor); }

 private:
  std::string title;
  std::string xAxisTitle;
  std::string yAxisTitle;
  float minimum;
  float maximum;
  float titleSize;
  float titleOffset;
  unsigned markerStyle;
  unsigned markerColor;
};

#endif
