#ifndef TNPFITTER_FITRESULT_H_
#define TNPFITTER_FITRESULT_H_ 1

#include <map>
#include <string>
#include <cassert>

class FitResult {
public:
  using SimpleParameter = std::pair<double, double>;
  using SimpleParameters = std::map<std::string, SimpleParameter>;

public:
  FitResult(const std::string& name, const std::size_t NPars = 0);
  ~FitResult();

public:
  int AddParameter(std::string name, double val, double error);
  const std::size_t GetNPars() const;
  const SimpleParameters& GetParameters() const;
  SimpleParameter GetParameter(const std::string& parName);
  double GetParValue(const std::string& name) const;
  double GetParError(const std::string& name) const;

private:
  std::string name;
  SimpleParameters parameters;
};

#endif
