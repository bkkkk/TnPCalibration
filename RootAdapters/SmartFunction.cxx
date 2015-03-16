#include "RootAdapters/SmartFunction.h"

#include <TF1.h>

namespace Smart {
TF1* Formula(std::string name,
             std::string formula,
             double fitMin,
             double FitMax) {
  return (new TF1(name.c_str(), formula.c_str(), fitMin, fitMax);
}
};
