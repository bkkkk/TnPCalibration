#ifndef EVENTWEIGHTING_H_
#define EVENTWEIGHTING_H_ 1

#include <map>
#include <string>

class IEvent;
class Weighting;

class EventWeighting {
 public:
  EventWeighting() = default;
  ~EventWeighting() = default;

 public:
  int AddWeighting(Weighting* weighting);

 public:
  double GetTotalWeighting(IEvent* event);

 public:
  Weighting* GetWeighting(const std::string& name);

 private:
  std::map<std::string, Weighting*> m_weightings;

#ifdef __CINT__
  ClassDef(EventWeighting, 1)
#endif
};

#endif
