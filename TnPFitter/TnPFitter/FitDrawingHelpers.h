#ifndef TNPFITTER_DRAWINGHELPERS_H_
#define TNPFITTER_DRAWINGHELPERS_H_ 1

#include "TnPFitter/IFitter.h"
#include "TnPFitter/FitterDraw.h"

namespace TNPFITTER {
  void DrawFit(IFitter* fitter, int sigma, int window);
};

#endif
