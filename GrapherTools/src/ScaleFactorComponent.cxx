#include "GrapherTools/ScaleFactorComponent.h"
#include "TH1.h"

SFComponent::SFComponent(std::unique_ptr<TH1> sfHistogram,
                         std::string sfTitle,
                         unsigned sfMarkerStyle,
                         unsigned sfMarkerColor)
    : histogram{std::move(sfHistogram)},
      title{sfTitle},
      markerStyle{sfMarkerStyle},
      markerColor{sfMarkerColor} {
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
