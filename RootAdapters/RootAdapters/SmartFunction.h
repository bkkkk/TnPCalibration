#ifndef ROOTADAPTERS_SMARTFUNCTION_H_
#define ROOTADAPTERS_SMARTFUNCTION_H_ 1

class TF1;

namespace Smart {
TF1* Formula(std::string name,
             std::string formula,
             double fitMin,
             double FitMax);
}

#endif
