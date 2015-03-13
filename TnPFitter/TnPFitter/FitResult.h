#ifndef TNPFITTER_FITRESULT_H_
#define TNPFITTER_FITRESULT_H_ 1

#include <map>
#include <string>

class FitResult {
public:
  using SimpleParameter = std::pair<double, double>;
  using SimpleParameters = std::map<std::string, SimpleParameter>;

public:
  FitResult() = default;

public:
  void AddParameter(std::string name, double val, double error);
  std::size_t GetNPars() const;
  const SimpleParameters& GetParameters() const;
  SimpleParameter GetParameter(const std::string& parName) const;
  double GetParValue(const std::string& name) const;
  double GetParError(const std::string& name) const;

private:
  SimpleParameters parameters;
};

#endif
