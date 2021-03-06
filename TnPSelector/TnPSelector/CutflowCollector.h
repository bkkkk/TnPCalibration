#ifndef TNPSELECTOR_CUTFLOWCOLLECTOR_H_
#define TNPSELECTOR_CUTFLOWCOLLECTOR_H_ 1

class CutflowCollector {
 public:
  CutflowCollector() = default;
  virtual ~CutflowCollector() = default;
public:
  virtual std::size_t getNCuts() const = 0;
  virtual const char* getCutName(unsigned index) const = 0;
  virtual bool getCutResult(unsigned index) const = 0;
};

#endif