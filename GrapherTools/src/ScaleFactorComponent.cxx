#include "GrapherTools/ScaleFactorComponent.h"
#include "TH1.h"

SFComponent::SFComponent(std::unique_ptr<TH1> histogram,
                         std::string title,
                         unsigned markerStyle,
                         unsigned markerColor)
    : histogram{std::move(histogram)},
      title{title},
      markerStyle{markerStyle},
      markerColor{markerColor} {
}

SFComponent::SFComponent(SFComponent& rhs)
    : histogram{rhs.histogram.release()},
      title{rhs.title},
      markerStyle{rhs.markerStyle},
      markerColor{rhs.markerColor} {
  histogram->SetMarkerColor(markerColor);
  histogram->SetLineColor(markerColor);
  histogram->SetMarkerStyle(markerStyle);
}

TH1* SFComponent::getHistogram() {
  return (histogram.get());
}

std::string SFComponent::getTitle() {
  return (title);
}
