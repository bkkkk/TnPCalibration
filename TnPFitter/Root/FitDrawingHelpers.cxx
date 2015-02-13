#include "TnPFitter/FitDrawingHelpers.h"

void TNPFITTER::DrawFit(IFitter* fitter, int sigma, int window) {
  if(fitter == nullptr) {
    throw(std::runtime_error("Fitter function not setup correctly"));
  }

  FitterDraw fitterDraw(fitter, sigma, window);
  fitterDraw.Draw();
}