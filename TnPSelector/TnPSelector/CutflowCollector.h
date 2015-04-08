#ifndef TNPSELECTOR_CUTFLOWCOLLECTOR_H_
#define TNPSELECTOR_CUTFLOWCOLLECTOR_H_ 1

class CutflowCollector {
 public:
  CutflowCollector();
  virtual ~CutflowCollector();
public:
  virtual std::size_t getNCuts() const = 0;
  virtual const char* getCutName(unsigned index) const = 0;
};

#endif