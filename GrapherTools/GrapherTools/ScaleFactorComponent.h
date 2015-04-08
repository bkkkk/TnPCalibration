#ifndef SCALEFACTOR_COMPONENTS_H_
#define SCALEFACTOR_COMPONENTS_H_ 1

#include <string>
#include <memory>

class TH1;

class SFComponent {
public:
  SFComponent(std::unique_ptr<TH1> histogram,
              std::string title,
              unsigned markerStyle,
              unsigned markerColor);
  SFComponent(SFComponent& rhs);

public:
  TH1* getHistogram();
  std::string getTitle();

private:
  std::unique_ptr<TH1> histogram;
  std::string title;
  unsigned markerStyle;
  unsigned markerColor;
};

#endif

