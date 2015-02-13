#ifndef TNPFITTER_CONFIGURATIONHELPERS_H_
#define TNPFITTER_CONFIGURATIONHELPERS_H_ 1

class TH1;

namespace TNPFITTER {
  bool IsLowBackground(TH1* histogram, double fittingEdge, double threshold);
}

#endif
