#include "GrapherTools/ScaleFactorAttributes.h"

SFAttributes::SFAttributes(std::string sfTitle)
    : title{std::move(sfTitle)},
      xAxisTitle{"x-axis"},
      yAxisTitle{"y-axis"},
      minimum{0},
      maximum{0},
      titleSize{10},
      titleOffset{0.5},
      markerStyle{21},
      markerColor{3} {
}

std::string SFAttributes::getTitle() {
  return (title);
}

std::string SFAttributes::getXAxisTitle() {
  return (xAxisTitle);
}

std::string SFAttributes::getYAxisTitle() {
  return (yAxisTitle);
}

float SFAttributes::getMinimum() {
  return (minimum);
}

float SFAttributes::getMaximum() {
  return (maximum);
}

SFAttributes SFAttributes::constructScaleFactorWithTitle(std::string sfTitle) {
  return (SFAttributes(sfTitle));
}

SFAttributes& SFAttributes::withRange(float min, float max) {
  minimum = min;
  maximum = max;
  return (*this);
}

SFAttributes& SFAttributes::withTitleSize(float size) {
  titleSize = size;
  return (*this);
}

SFAttributes& SFAttributes::withTitleOffset(float offset) {
  titleOffset = offset;
  return (*this);
}

SFAttributes& SFAttributes::withMarkerStyle(unsigned style) {
  markerStyle = style;
  return (*this);
}

SFAttributes& SFAttributes::withMarkerColor(unsigned color) {
  markerColor = color;
  return (*this);
}

SFAttributes& SFAttributes::withXAxisTitle(std::string axisTitle) {
  xAxisTitle = std::move(axisTitle);
  return (*this);
}

SFAttributes& SFAttributes::withYAxisTitle(std::string axisTitle) {
  yAxisTitle = std::move(axisTitle);
  return (*this);
}
